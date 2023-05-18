#include "system_agent.h"

SystemAgent::SystemAgent(const AgentSettings &settings) : Agent(settings) {}

Agent * SystemAgent::create(const AgentSettings &settings) {
  return new SystemAgent(settings);
}

const QHash<QString, Metric> & SystemAgent::getMetrics() const {
  return m_settings.m_metrics;
}