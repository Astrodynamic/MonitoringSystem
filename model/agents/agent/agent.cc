#include "agent.h"

Agent::Agent(const AgentSettings &settings) : m_settings(settings) {
  m_settings.m_timer.start();
}

auto Agent::Settings() -> AgentSettings & { return m_settings; }

auto Agent::Settings() const -> const AgentSettings & { return m_settings; }
