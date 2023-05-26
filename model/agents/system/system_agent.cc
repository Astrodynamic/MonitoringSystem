#include "system_agent.h"

SystemAgent::SystemAgent(const AgentSettings &settings) : Agent(settings) {}

auto SystemAgent::Metrics() const -> const QHash<QString, Metric> & {
  return m_settings.m_metrics;
}