#pragma once

#include "agent_manager.h"

class Kernel : public QObject {
    Q_OBJECT
    Q_PROPERTY(AgentManager* agentManager READ agentManager CONSTANT)

 public:
    explicit Kernel(QObject *parent = nullptr);

    AgentManager *agentManager() const;

 private:
    AgentManager *m_agent_manager;
};
