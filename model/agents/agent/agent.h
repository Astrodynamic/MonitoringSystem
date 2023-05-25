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

 protected:
  AgentSettings m_settings;
};

#define Agent_iid "MonitoringSystem.Agent/1.0"

Q_DECLARE_INTERFACE(Agent, Agent_iid)
