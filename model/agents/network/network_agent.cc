#include "network_agent.h"

#ifdef __cplusplus
extern "C" {
#endif

Agent* __create(const AgentSettings settings) {
  return new NetworkAgent(settings);
}

#ifdef __cplusplus
}
#endif

NetworkAgent::NetworkAgent(const AgentSettings& settings) : Agent(settings) {}

auto NetworkAgent::Metrics() -> const QHash<QString, Metric>& {
  return m_settings.m_metrics;
}
