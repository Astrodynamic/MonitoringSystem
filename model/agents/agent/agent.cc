#include "agent.h"

auto Agent::Settings() -> AgentSettings & {
  return m_settings;
}

auto Agent::Settings() const -> const AgentSettings & {
  return m_settings;
}

