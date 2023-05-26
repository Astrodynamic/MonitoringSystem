#include "network_agent.h"

extern "C" {
  Agent* __create(const AgentSettings settings) { return new NetworkAgent(settings); }
}

NetworkAgent::NetworkAgent(const AgentSettings &settings) : Agent(settings) {}

auto NetworkAgent::Metrics() const -> const QHash<QString, Metric> & {
  return m_settings.m_metrics;
}