#include "cpu_agent.h"

extern "C" {
#include <stdlib.h>
#include <sys/sysinfo.h>
  Agent* __create(const AgentSettings settings) { return new CpuAgent(settings); }

  static double GetCpuLoad() {
    double avg[3];
    int loads = getloadavg(avg, 3);

    return avg[0];
  }

  static int GetProcessesCount() {
    struct sysinfo info;
    if (0 == sysinfo(&info)) {
      return info.procs;
    }
    return 0;
  }

}

CpuAgent::CpuAgent(const AgentSettings &settings) : Agent(settings) {}

auto CpuAgent::Metrics() -> const QHash<QString, Metric> & {
  m_settings.m_metrics["cpu"].value = GetCpuLoad();
  m_settings.m_metrics["processes"].value = GetProcessesCount();

  return m_settings.m_metrics;
}
