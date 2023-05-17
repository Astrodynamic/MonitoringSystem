#include "system_agent.h"

SystemAgent::SystemAgent(const AgentSettings &settings) : Agent(settings) {}

QHash<QString, Metric> SystemAgent::getMetrics() {
  QHash<QString, Metric> metrics;
  Metric metric;
  return metrics;
}