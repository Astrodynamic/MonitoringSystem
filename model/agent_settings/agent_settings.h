#pragma once

#include <QDir>
#include <QElapsedTimer>
#include <QHash>
#include <QPair>
#include <QString>
#include <QTime>
#include <QVariant>

struct AgentSettings {
  QString m_name;
  QString m_type;
  QTime m_interval;
  QFileInfo m_config;
  QElapsedTimer m_timer;
  QHash<QString, QVariant> m_metrics;
};