#include "kernel.h"

Kernel::Kernel(QObject *parent)
  : QObject(parent)
  , m_agent_manager(new AgentManager(this)) {
    AgentSettings settings;
    m_agent_manager->registerAgent(settings);
}

Kernel::~Kernel() {
  delete m_agent_manager;
}

AgentManager *Kernel::agentManager() const {
  return m_agent_manager;
}
