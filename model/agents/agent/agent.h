#pragma once

#include "agent_settings.h"

class Agent {
public:
  Agent() = default;
  explicit Agent(const Agent & other) = delete;
  explicit Agent(Agent && other) = delete;
  virtual ~Agent() = default;

  auto operator=(const Agent & other) -> Agent & = delete;
  auto operator=(Agent && other) -> Agent & = delete;

  virtual auto Metrics() const -> const QHash<QString, Metric> & = 0;
  
  auto Settings() const -> const AgentSettings &;
  auto Settings() -> AgentSettings &;

 protected:
  AgentSettings m_settings;
};
