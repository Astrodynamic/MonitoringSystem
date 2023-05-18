#include "system_agent.h"

SystemAgent::SystemAgent(const AgentSettings &settings) : Agent(settings) {}

const QHash<QString, Metric> & SystemAgent::getMetrics() const {
  QHash<QString, Metric> metrics;
  return metrics;
}