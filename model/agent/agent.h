#pragma once

#include "agent_settings.h"

class Agent {
 public:
  Agent() = default;
  virtual ~Agent() = default;

  virtual QHash<QString, QPair<QVariant, QVariant> > getMetrics() = 0;

 protected:
  AgentSettings m_settings;
};