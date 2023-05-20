#include "kernel.h"

Kernel::Kernel(QObject *parent)
  : QObject(parent)
  , m_agent_manager(new AgentManager(this))
  , m_watcher_manager(new WatcherManager(QDir::currentPath(), this)) {
    m_watcher_manager->setRoot("/opt/goinfre/werewolf/Documents/github/MonitoringSystem/agents");

    connect(m_watcher_manager, &WatcherManager::FileDetected, [this](QString conf, QString lib) {
      qDebug() << "File detected" << conf << lib;
    });

    // AgentSettings settings;
    // m_agent_manager->registerAgent(settings);
}

Kernel::~Kernel() {
  delete m_agent_manager;
}

AgentManager *Kernel::agentManager() const {
  return m_agent_manager;
}
