#include "agent.h"

Agent::Agent(const AgentSettings &settings) : m_settings(settings) {}

AgentSettings & Agent::getSettings() {
  return m_settings;
}

const AgentSettings & Agent::getSettings() const {
  return m_settings;
}
