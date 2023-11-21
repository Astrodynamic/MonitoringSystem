#include "network_agent.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

static int GetNetworkAvailabiliry() {
  FILE* ping;
  char buffer[128];
  memset(&buffer, 0, 128);

  ping = popen("ping 8.8.8.8 -c 1 | grep \"1 received\"", "r");
  if (NULL != ping) {
    fgets(buffer, 128, ping);
    pclose(ping);
  }

  return (strlen(buffer) == 0) ? 0 : 1;
}

static int GetInetThroughput() {
  FILE* speed;
  char buffer[128];
  memset(&buffer, 0, 128);

  speed = popen("cat /sys/class/net/enp5s0/speed", "r");
  if (NULL != speed) {
    fgets(buffer, 128, speed);
    pclose(speed);

    int value;
    sscanf(buffer, "%d", &value);
    if (0 < value) return value;
  }

  return -1;
}

Agent* __create(const AgentSettings settings) {
  return new NetworkAgent(settings);
}

#ifdef __cplusplus
}
#endif

NetworkAgent::NetworkAgent(const AgentSettings& settings) : Agent(settings) {}

auto NetworkAgent::Metrics() -> const QHash<QString, Metric>& {
  m_settings.m_metrics["network_availability"].value = GetNetworkAvailabiliry();

  m_settings.m_metrics["inet_throughput"].value = GetInetThroughput();

  return m_settings.m_metrics;
}
