#include "agent.h"

AgentSettings & Agent::Settings() {
    return m_settings;
}

const AgentSettings & Agent::Settings() const {
  return m_settings;
}

