#pragma once

#include <QObject>
#include <QtPlugin>

#include "agent.h"

#define PLUGIN_NAME "agent.json"

class CpuAgent final : public QObject, public Agent {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MonitoringSystem.Agent/1.0" FILE PLUGIN_NAME)
    Q_INTERFACES(Agent)
 public:
  CpuAgent() = default;
  ~CpuAgent() = default;

  virtual const QHash<QString, Metric> & getMetrics() const override final;
};
