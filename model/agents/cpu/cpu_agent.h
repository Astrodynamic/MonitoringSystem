#pragma once

#include "agent.h"

class CpuAgent final : public Agent {
 public:
  CpuAgent() = default;
  ~CpuAgent() = default;

  virtual const QHash<QString, Metric> & Metrics() const override final;
};
