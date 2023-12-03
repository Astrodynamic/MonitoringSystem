#pragma once

#include <QDir>
#include <QElapsedTimer>
#include <QHash>
#include <QPair>
#include <QSharedPointer>
#include <QString>
#include <QTime>
#include <QTimer>
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
  QVariant comparisonValue;
};

struct AgentSettings {
  bool m_enabled;
  QString m_name;
  QString m_type;
  QSharedPointer<QTimer> m_interval;
  QFileInfo m_config;
  QElapsedTimer m_timer;
  QHash<QString, Metric> m_metrics;
};
