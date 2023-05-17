#include "cpu_agent.h"

CpuAgent::CpuAgent(const AgentSettings &settings) : Agent(settings) {}

QHash<QString, Metric> CpuAgent::getMetrics() {
  QHash<QString, Metric> metrics;
  Metric metric;
  return metrics;
}