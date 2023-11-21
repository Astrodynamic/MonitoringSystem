#include "system_agent.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>

static void GetCPULevels(double *idle, double *user, double *priveleged,
                         double *dpc, double *interrupt) {
  FILE *cpustat;
  char buffer[128];
  memset(&buffer, 0, 128);

  cpustat = popen(
      "awk 'NR<2 {printf(\"%d %d %d %d %d\", $5, $2, $4, $8, $7)}' /proc/stat",
      "r");
  if (NULL != cpustat) {
    fgets(buffer, 128, cpustat);
    pclose(cpustat);

    sscanf(buffer, "%lf %lf %lf %lf %lf", idle, user, priveleged, dpc,
           interrupt);

    double sum = *idle + *user + *priveleged + *dpc + *interrupt;
    *idle = *idle / sum * 100.;
    *user = *user / sum * 100.;
    *priveleged = *priveleged / sum * 100.;
    *dpc = *dpc / sum * 100.;
    *interrupt = *interrupt / sum * 100.;
  }
}

// returns in Gb
static void GetSWAPInfo(double *total, double *used) {
  struct sysinfo info;
  if (0 == sysinfo(&info)) {
    *total = info.totalswap / 1024 / 1024 / 1024.;
    *used = (info.totalswap - info.freeswap) / 1024 / 1024 / 1024.;
  }
}

static int GetRunningProccessesCount() {
  FILE *running_proccesses;
  char buffer[128];
  memset(&buffer, 0, 128);

  running_proccesses = popen("ps -e -o stat | grep \"^R\" | wc -l", "r");
  if (NULL != running_proccesses) {
    fgets(buffer, 128, running_proccesses);
    pclose(running_proccesses);

    int count;
    sscanf(buffer, "%d", &count);

    return count;
  }

  return 0;
}

static int GetInodesCount() {
  FILE *inodes;
  char buffer[128];
  memset(&buffer, 0, 128);

  inodes = popen("df -i / | awk 'NR>1 {print $2}'", "r");
  if (NULL != inodes) {
    fgets(buffer, 128, inodes);
    pclose(inodes);

    int count;
    sscanf(buffer, "%d", &count);

    return count;
  }

  return 0;
}

// returns in MiB
static double GetHardReadTime() {
  FILE *ioping;
  char buffer[128];
  memset(&buffer, 0, 128);

  ioping = popen("ioping -R /tmp/ | grep read | awk '{print $8}'", "r");
  if (NULL != ioping) {
    fgets(buffer, 128, ioping);
    pclose(ioping);

    double speed;
    sscanf(buffer, "%lf", &speed);

    return speed;
  }

  return 0;
}

static int GetSystemErrors() {
  FILE *syslog;
  char buffer[128];
  memset(&buffer, 0, 128);

  syslog = popen("grep error /var/log/syslog | wc -l", "r");
  if (NULL != syslog) {
    fgets(buffer, 128, syslog);
    pclose(syslog);

    int count;
    sscanf(buffer, "%d", &count);

    return count;
  }

  return 0;
}

static int GetUserAuths() {
  FILE *auth;
  char buffer[128];
  memset(&buffer, 0, 128);

  auth = popen("grep \"session opened\" /var/log/auth.log | wc -l", "r");
  if (NULL != auth) {
    fgets(buffer, 128, auth);
    pclose(auth);

    int count;
    sscanf(buffer, "%d", &count);

    return count;
  }

  return 0;
}

Agent *__create(const AgentSettings settings) {
  return new SystemAgent(settings);
}

#ifdef __cplusplus
}
#endif

SystemAgent::SystemAgent(const AgentSettings &settings) : Agent(settings) {}

auto SystemAgent::Metrics() -> const QHash<QString, Metric> & {
  double idle, user, priveleged, dpc, interrupt;
  idle = user = priveleged = dpc = interrupt = 0.0;
  GetCPULevels(&idle, &user, &priveleged, &dpc, &interrupt);
  m_settings.m_metrics["cpu_idle_usage"].value = idle;
  m_settings.m_metrics["cpu_user_usage"].value = user;
  m_settings.m_metrics["cpu_privileged_usage"].value = priveleged;
  m_settings.m_metrics["cpu_dpc_usage"].value = dpc;
  m_settings.m_metrics["cpu_interrupt_usage"].value = interrupt;

  double swap_total = 0.0, swap_used = 0.0;
  GetSWAPInfo(&swap_total, &swap_used);
  m_settings.m_metrics["total_swap"].value = swap_total;
  m_settings.m_metrics["used_swap"].value = swap_used;

  m_settings.m_metrics["proc_queue_length"].value = GetRunningProccessesCount();

  m_settings.m_metrics["inodes"].value = GetInodesCount();

  m_settings.m_metrics["hard_read_time"].value = GetHardReadTime();

  m_settings.m_metrics["system_errors"].value = GetSystemErrors();

  m_settings.m_metrics["user_auths"].value = GetUserAuths();

  return m_settings.m_metrics;
}
