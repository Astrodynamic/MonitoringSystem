#include "memory_agent.h"

MemoryAgent::MemoryAgent(const AgentSettings &settings) : Agent(settings) {}

auto MemoryAgent::Metrics() const -> const QHash<QString, Metric> & {
  return m_settings.m_metrics;
}