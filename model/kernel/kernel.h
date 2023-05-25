#pragma once

#include <QDir>

#include "agent_manager.h"
#include "config_manager.h"
#include "watcher_manager.h"

class Kernel : public QObject {
  Q_OBJECT
  Q_PROPERTY(AgentManager *agentManager READ agentManager CONSTANT)

 public:
  explicit Kernel(QObject *parent = nullptr);
  virtual ~Kernel();

  AgentManager *agentManager() const;

 private:
  AgentManager *m_agent_manager;
  WatcherManager *m_watcher_manager;
  ConfigurationManager *m_config_manager;
};
