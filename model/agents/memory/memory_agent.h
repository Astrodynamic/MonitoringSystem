#pragma once

#include "agent.h"

class MemoryAgent final : public Agent {
 public:
  MemoryAgent() = default;
  explicit MemoryAgent(const AgentSettings &settings);
  ~MemoryAgent() = default;

  virtual auto Metrics() -> const QHash<QString, Metric> & override final;
};
