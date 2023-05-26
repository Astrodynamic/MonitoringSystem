#include "kernel.h"

Kernel::Kernel(QObject *parent)
    : QObject(parent),
      m_log_manager(new LogManager(this)),
      m_agent_manager(new AgentManager(this)),
      m_watcher_manager(new WatcherManager(QString(BUILD_DIR), this)),
      m_config_manager(new ConfigurationManager(this)) {

  connect(m_watcher_manager, &WatcherManager::FileDetected, [this](const QString conf, QString lib) {
            AgentSettings settings;
            m_config_manager->loadConfiguration(conf, settings);
            m_agent_manager->registerAgent(lib, settings);
          });

  m_watcher_manager->setRoot(QString(BUILD_DIR) + QDir::separator() + "agents");
}

Kernel::~Kernel() {
  delete m_log_manager;
  delete m_agent_manager;
  delete m_watcher_manager;
  delete m_config_manager;
}

auto Kernel::agentManager() const -> AgentManager * {
  return m_agent_manager;
}
