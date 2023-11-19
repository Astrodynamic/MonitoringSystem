#pragma once

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "agent_settings.h"

class ConfigurationManager : public QObject {
  Q_OBJECT

 public:
  explicit ConfigurationManager(QObject *parent = nullptr);
  virtual ~ConfigurationManager();

 public slots:
  auto loadConfiguration(const QString & path, AgentSettings &settings) -> bool;
};
