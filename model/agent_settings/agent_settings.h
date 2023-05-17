#pragma once

#include <QDir>
#include <QElapsedTimer>
#include <QHash>
#include <QPair>
#include <QString>
#include <QTime>
#include <QVariant>

enum class ComparisonOperator {
  kLessThan = 0,
  kLessThanOrEqualTo,
  kEqualTo,
  kGreaterThanOrEqualTo,
  kGreaterThan
};

struct Metric {
  QVariant value;
  ComparisonOperator op;
};

struct AgentSettings {
  bool m_enabled;
  QString m_name;
  QString m_type;
  QTime m_interval;
  QFileInfo m_config;
  QElapsedTimer m_timer;
  QHash<QString, Metric> m_metrics;
};
