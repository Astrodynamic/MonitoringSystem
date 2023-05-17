#include "network_agent.h"

NetworkAgent::NetworkAgent(const AgentSettings &settings) : Agent(settings) {}

QHash<QString, Metric> NetworkAgent::getMetrics() {
  QHash<QString, Metric> metrics;
  Metric metric;
  return metrics;
}