#pragma once

#include "agent.h"

class NetworkAgent final : public Agent {
 public:
  NetworkAgent() = default;
  explicit NetworkAgent(const AgentSettings &settings);
  ~NetworkAgent() = default;

  virtual const QHash<QString, Metric> & getMetrics() const override final;
};