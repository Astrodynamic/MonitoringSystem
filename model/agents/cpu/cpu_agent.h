#pragma once

#include "agent.h"

class CpuAgent final : public Agent {
 public:
  CpuAgent() = default;
  explicit CpuAgent(const AgentSettings &settings);
  ~CpuAgent() = default;

  virtual auto Metrics() const -> const QHash<QString, Metric> & override final;
};
