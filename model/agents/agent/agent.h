#pragma once

#include "agent_settings.h"

class Agent {
 public:
  Agent() = default;
  virtual ~Agent() = default;

  virtual QHash<QString, QPair<QVariant, QVariant>> getMetrics(){}
  AgentSettings getSettings() const;

  protected:
  AgentSettings m_settings;
};
