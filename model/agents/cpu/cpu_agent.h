#pragma once

#include "agent.h"

class CpuAgent : public Agent {
 public:
  void updateMetrics() override;
};