#pragma once

#include "agent.h"

class CpuAgent final : public Agent {
 public:
  CpuAgent() = default;
  explicit CpuAgent(const AgentSettings &settings);
  ~CpuAgent() = default;

  static  Agent * create(const AgentSettings &settings);

  virtual const QHash<QString, Metric> & getMetrics() const override final;
};
