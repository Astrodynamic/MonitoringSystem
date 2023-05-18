#include "kernel.h"

Kernel::Kernel(QObject *parent)
  : QObject(parent)
  , m_agent_manager(new AgentManager(this)) {
}

Kernel::~Kernel() {
  delete m_agent_manager;
}

AgentManager *Kernel::agentManager() const {
  return m_agent_manager;
}
