#include "system_agent.h"

#ifdef __cplusplus
extern "C" {
#endif
  Agent* __create(const AgentSettings settings) { return new SystemAgent(settings); }
#ifdef __cplusplus
}
#endif

SystemAgent::SystemAgent(const AgentSettings &settings) : Agent(settings) {}

auto SystemAgent::Metrics() -> const QHash<QString, Metric> & {
  return m_settings.m_metrics;
}
