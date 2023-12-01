#include "kernel.h"

Kernel::Kernel(QObject *parent)
    : QObject(parent),
      m_log_manager(new LogManager(QString(PROJECT_FOLDER), this)),
      m_agent_manager(new AgentManager(this)),
      m_watcher_manager(new WatcherManager(QDir::homePath(), this)),
      m_config_manager(new ConfigurationManager(this)),
      m_notification_manager(new NotificationManager(this)) {

  m_log_manager->BufferSize(20);

  connect(m_watcher_manager, &WatcherManager::FileDetected, [this](const QString conf, QString lib) {
            AgentSettings settings;
            m_config_manager->loadConfiguration(conf, settings);
            m_agent_manager->registerAgent(lib, settings);
          });

  m_watcher_manager->setRoot(QString(PROJECT_FOLDER) + QDir::separator() + "agents");

  connect(m_agent_manager, &AgentManager::updateConfiguration, m_config_manager, &ConfigurationManager::loadConfiguration);
  connect(m_agent_manager, &AgentManager::updateLogs, m_log_manager, &LogManager::Write);
}

Kernel::~Kernel() {
  delete m_log_manager;
  delete m_agent_manager;
  delete m_watcher_manager;
  delete m_config_manager;
  delete m_notification_manager;
}

auto Kernel::agentManager() const -> AgentManager * {
    return m_agent_manager;
}

auto Kernel::logManager() const -> LogManager * {
    return m_log_manager;
}
