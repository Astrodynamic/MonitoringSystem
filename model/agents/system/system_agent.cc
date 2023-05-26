#include "system_agent.h"

extern "C" {
  Agent* __create(const AgentSettings settings) { return new SystemAgent(settings); }
}

SystemAgent::SystemAgent(const AgentSettings &settings) : Agent(settings) {}

auto SystemAgent::Metrics() const -> const QHash<QString, Metric> & {
  return m_settings.m_metrics;
}