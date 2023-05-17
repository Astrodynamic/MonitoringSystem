#pragma once

#include <QDir>
#include <QElapsedTimer>
#include <QHash>
#include <QPair>
#include <QString>
#include <QTime>
#include <QVariant>

struct AgentSettings {
  bool m_enabled;
  QString m_name;
  QString m_type;
  QTime m_interval;
  QFileInfo m_config;
  QElapsedTimer m_timer;
  QHash<QString, QPair<QString, QVariant> > m_metrics;
};