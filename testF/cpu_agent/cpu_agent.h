#pragma once

#include <QtPlugin>
#include <QDebug>
#include <QObject>

#include "agent.h"

#define PLUGIN_NAME "agent.json"

#pragma once

#include "agent.h"

class CpuAgent final : public QObject, public Agent {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MonitoringSystem.Agent/1.0" FILE PLUGIN_NAME)
    Q_INTERFACES(Agent)
 public:
  CpuAgent() = default;
  explicit CpuAgent(const AgentSettings &settings);
  ~CpuAgent() = default;

  virtual const QHash<QString, Metric> & getMetrics() const override final;
};

