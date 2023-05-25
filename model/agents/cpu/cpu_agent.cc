#include "cpu_agent.h"

const QHash<QString, Metric> & CpuAgent::getMetrics() const {
    qDebug() << "get metrics test";
  return m_settings.m_metrics;
}
