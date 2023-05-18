#include "network_agent.h"

NetworkAgent::NetworkAgent(const AgentSettings &settings) : Agent(settings) {}

Agent * NetworkAgent::create(const AgentSettings &settings) {
  return new NetworkAgent(settings);
}

const QHash<QString, Metric> & NetworkAgent::getMetrics() const {
  return m_settings.m_metrics;
}