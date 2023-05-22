#pragma once

#include <QSettings>
#include <QObject>

#include "agent_settings.h"

class ConfigurationManager : public QObject {
  Q_OBJECT

 public:
  explicit ConfigurationManager(QObject *parent = nullptr);
  virtual ~ConfigurationManager();

  bool loadConfiguration(QString & path, AgentSettings &settings);
};