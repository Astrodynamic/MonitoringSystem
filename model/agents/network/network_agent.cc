#include "network_agent.h"

NetworkAgent::NetworkAgent(const AgentSettings &settings) : Agent(settings) {}

auto NetworkAgent::Metrics() const -> const QHash<QString, Metric> & {
  return m_settings.m_metrics;
}