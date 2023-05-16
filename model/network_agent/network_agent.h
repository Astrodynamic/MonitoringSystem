#pragma once

#include "agent.h"

class NetworkAgent : public Agent {
 public:
  void updateMetrics() override;
};