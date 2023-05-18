#pragma once

#include "agent.h"

class SystemAgent final : public Agent {
 public:
  SystemAgent() = default;
  explicit SystemAgent(const AgentSettings &settings);
  ~SystemAgent() = default;

  static Agent * create(const AgentSettings &settings);

  virtual const QHash<QString, Metric> & getMetrics() const override final;
};