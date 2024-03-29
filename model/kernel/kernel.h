#pragma once

#include <QDir>

#include "agent_manager.h"
#include "config_manager.h"
#include "log_manager.h"
#include "notification_manager.h"
#include "watcher_manager.h"

class Kernel : public QObject {
  Q_OBJECT
  Q_PROPERTY(AgentManager *agentManager READ agentManager CONSTANT)
  Q_PROPERTY(LogManager *logManager READ logManager CONSTANT)
  Q_PROPERTY(NotificationManager *notificationManager READ notificationManager CONSTANT)

 public:
  explicit Kernel(QObject *parent = nullptr);
  virtual ~Kernel();

  auto agentManager() const -> AgentManager *;
  auto logManager() const -> LogManager *;
  auto notificationManager() const -> NotificationManager *;

 private:
  LogManager *m_log_manager;
  AgentManager *m_agent_manager;
  WatcherManager *m_watcher_manager;
  ConfigurationManager *m_config_manager;
  NotificationManager *m_notification_manager;
};
