#include "cpu_agent.h"

auto CpuAgent::Metrics() const -> const QHash<QString, Metric> & {
  return m_settings.m_metrics;
}
