#pragma once

#include "agent.h"

class SystemAgent final : public Agent {
 public:
  SystemAgent() = default;
  explicit SystemAgent(const AgentSettings &settings);
  ~SystemAgent() = default;

  virtual QHash<QString, Metric> getMetrics() override final;
};