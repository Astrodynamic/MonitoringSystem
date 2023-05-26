#pragma once

#include "agent_settings.h"

class Agent {
public:
  Agent() = default;
  explicit Agent(const Agent & other) = delete;
  explicit Agent(Agent && other) = delete;
  virtual ~Agent() = default;

  Agent & operator=(const Agent & other) = delete;
  Agent & operator=(Agent && other) = delete;

  virtual const QHash<QString, Metric> & Metrics() const = 0;
  
  const AgentSettings & Settings() const;
  AgentSettings & Settings();

 protected:
  AgentSettings m_settings;
};
