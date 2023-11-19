#include "memory_agent.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
Agent *__create(const AgentSettings settings) {
  return new MemoryAgent(settings);
}

// returns in Gb
static double GetRAMTotal() {
  struct sysinfo info;
  if (0 == sysinfo(&info)) {
    return info.totalram / 1024 / 1024 / 1024.;
  }
  return 0;
}

static double GetRAMLoad() {
  struct sysinfo info;
  if (0 == sysinfo(&info)) {
    return (info.totalram - info.freeram) / (info.totalram * 100.);
  }
  return 0;
}

static double GetHardVolume() {
  struct statvfs memory;
  if (0 == statvfs("/", &memory)) {
    const double total = memory.f_blocks * memory.f_frsize;
    const double total_free = memory.f_bavail * memory.f_frsize;
    const double used = total - total_free;

    return (used / total) * 100.;
  }
  return 0;
}

static void GetHardIO(int *hard_ops, double *hard_throughput) {
  FILE *iostat;
  char buffer[128];
  memset(buffer, 0, 128);

  iostat = popen(
      "iostat | awk 'BEGIN {hard_ops = 0; hard_throughput = 0;} {hard_ops = "
      "hard_ops + $2; hard_throughput = hard_throughput + $3 + $4;} END "
      "{printf \"%.0f %f\", hard_ops, hard_throughput}'",
      "r");
  if (NULL != iostat) {
    char *dot = NULL;
    if (NULL != (dot = strchr(buffer, ','))) {
      *dot = '.';
    }
    sscanf(buffer, "%d %lf", hard_ops, hard_throughput);
    pclose(iostat);
  }
}
#ifdef __cplusplus
}
#endif

MemoryAgent::MemoryAgent(const AgentSettings &settings) : Agent(settings) {}

auto MemoryAgent::Metrics() -> const QHash<QString, Metric> & {
  m_settings.m_metrics["ram_total"].value = GetRAMTotal();
  m_settings.m_metrics["ram"].value = GetRAMLoad();
  m_settings.m_metrics["hard_volume"].value = GetHardVolume();

  int hard_ops = 0;
  double hard_throughput = 0.0;
  GetHardIO(&hard_ops, &hard_throughput);
  m_settings.m_metrics["hard_ops"].value = hard_ops;
  m_settings.m_metrics["hard_throughput"].value = hard_throughput;

  return m_settings.m_metrics;
}
