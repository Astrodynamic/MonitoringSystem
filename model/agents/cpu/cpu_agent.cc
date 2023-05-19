#include "cpu_agent.h"

CpuAgent::CpuAgent(const AgentSettings &settings) : Agent(settings) {}

Agent * CpuAgent::create(const AgentSettings &settings) {
  return new CpuAgent(settings);
}

const QHash<QString, Metric> & CpuAgent::getMetrics() const {
  return m_settings.m_metrics;
}
