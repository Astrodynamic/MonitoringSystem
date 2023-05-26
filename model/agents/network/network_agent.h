#pragma once

#include "agent.h"

class NetworkAgent final : public Agent {
 public:
  NetworkAgent() = default;
  explicit NetworkAgent(const AgentSettings &settings);
  ~NetworkAgent() = default;

  static Agent * create(const AgentSettings &settings);

  virtual const QHash<QString, Metric> & Metrics() const override final;
};