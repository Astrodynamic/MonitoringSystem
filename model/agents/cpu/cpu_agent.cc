#include "cpu_agent.h"

CpuAgent::CpuAgent(const AgentSettings &settings) : Agent(settings) {}

const QHash<QString, Metric> & CpuAgent::getMetrics() const {
    qDebug() << "get metrics test";
  return m_settings.m_metrics;
}
