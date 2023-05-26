#include "cpu_agent.h"

extern "C" {
  Agent* __create(const AgentSettings settings) { return new CpuAgent(settings); }
}

CpuAgent::CpuAgent(const AgentSettings &settings) : Agent(settings) {}

auto CpuAgent::Metrics() const -> const QHash<QString, Metric> & {
  return m_settings.m_metrics;
}
