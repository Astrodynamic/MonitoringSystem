#include "cpu_agent.h"

CpuAgent::CpuAgent(const AgentSettings &settings) : Agent(settings) {}

const QHash<QString, Metric> & CpuAgent::getMetrics() const {
  QHash<QString, Metric> metrics;
  return metrics;
}