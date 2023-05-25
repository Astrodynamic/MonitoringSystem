#include "agent.h"

AgentSettings & Agent::getSettings() {
    return m_settings;
}

void Agent::setSettings(const AgentSettings & new_settings)
{
    m_settings = new_settings;
}

const AgentSettings & Agent::getSettings() const {
  return m_settings;
}

