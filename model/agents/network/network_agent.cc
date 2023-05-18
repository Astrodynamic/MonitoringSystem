#include "network_agent.h"

NetworkAgent::NetworkAgent(const AgentSettings &settings) : Agent(settings) {}

const QHash<QString, Metric> & NetworkAgent::getMetrics() const {
  QHash<QString, Metric> metrics;
  return metrics;
}