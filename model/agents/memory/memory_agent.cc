#include "memory_agent.h"

MemoryAgent::MemoryAgent(const AgentSettings &settings) : Agent(settings) {}

QHash<QString, Metric> MemoryAgent::getMetrics() {
  QHash<QString, Metric> metrics;
  Metric metric;
  return metrics;
}