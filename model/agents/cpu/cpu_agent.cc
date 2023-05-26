#include "cpu_agent.h"

const QHash<QString, Metric> & CpuAgent::Metrics() const {
  return m_settings.m_metrics;
}
