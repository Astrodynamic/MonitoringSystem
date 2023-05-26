#include "memory_agent.h"

MemoryAgent::MemoryAgent(const AgentSettings &settings) : Agent(settings) {}

Agent * MemoryAgent::create(const AgentSettings &settings) {
  return new MemoryAgent(settings);
}

const QHash<QString, Metric> & MemoryAgent::Metrics() const {
  return m_settings.m_metrics;
}