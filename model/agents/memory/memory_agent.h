#pragma once

#include "agent.h"

class MemoryAgent final : public Agent {
 public:
  MemoryAgent() = default;
  explicit MemoryAgent(const AgentSettings &settings);
  ~MemoryAgent() = default;

  static Agent * create(const AgentSettings &settings);

  virtual const QHash<QString, Metric> & getMetrics() const override final;
};