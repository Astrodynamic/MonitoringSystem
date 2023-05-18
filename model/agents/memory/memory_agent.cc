#include "memory_agent.h"

MemoryAgent::MemoryAgent(const AgentSettings &settings) : Agent(settings) {}

const QHash<QString, Metric> & MemoryAgent::getMetrics() const {
  QHash<QString, Metric> metrics;
  return metrics;
}