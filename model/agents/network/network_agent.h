#pragma once

#include "agent.h"

class NetworkAgent final : public Agent {
 public:
  NetworkAgent() = default;
  explicit NetworkAgent(const AgentSettings &settings);
  ~NetworkAgent() = default;

  virtual QHash<QString, Metric> getMetrics() override final;
};