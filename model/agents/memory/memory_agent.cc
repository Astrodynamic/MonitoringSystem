#include "memory_agent.h"

extern "C" {
  Agent* __create(const AgentSettings settings) { return new MemoryAgent(settings); }
}

MemoryAgent::MemoryAgent(const AgentSettings &settings) : Agent(settings) {}

auto MemoryAgent::Metrics() const -> const QHash<QString, Metric> & {
  return m_settings.m_metrics;
}