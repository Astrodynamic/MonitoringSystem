#pragma once

#include "agent.h"

class MemoryAgent : public Agent {
 public:
  void updateMetrics() override;
};