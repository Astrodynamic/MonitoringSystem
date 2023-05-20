#pragma once

#include "agent_settings.h"

class Agent {
 public:
  Agent() = default;
  explicit Agent(const AgentSettings &settings);
  explicit Agent(const Agent & other) = delete;
  explicit Agent(Agent && other) = delete;
  virtual ~Agent() = default;

  Agent & operator=(const Agent & other) = delete;
  Agent & operator=(Agent && other) = delete;

  virtual const QHash<QString, Metric> & getMetrics() const = 0;
  
  const AgentSettings & getSettings() const;
  AgentSettings & getSettings();

  virtual Agent * create(const AgentSettings &settings);

 protected:
  AgentSettings m_settings;
};
