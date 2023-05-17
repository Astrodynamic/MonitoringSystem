#pragma once

#include "agent_settings.h"

class Agent {
 public:
  Agent() = default;
  virtual ~Agent() = default;

  void setName(const QString &name);
  void setType(const QString &type);

  QString getName() const;
  QString getType() const;

  virtual QHash<QString, QPair<QVariant, QVariant>> getMetrics(){};

  protected:
  AgentSettings m_settings;
};
