#pragma once

#include "agent.h"

class NetworkAgent final : public Agent {
 public:
  NetworkAgent() = default;
  explicit NetworkAgent(const AgentSettings &settings);
  ~NetworkAgent() = default;

  virtual auto Metrics() -> const QHash<QString, Metric> & override final;
};
