#include "agent.h"

void Agent::setName(const QString &name) {
  m_settings.m_name = name;
}

void Agent::setType(const QString &type) {
  m_settings.m_type = type;
}

QString Agent::getName() const {
  return m_settings.m_name;
}

QString Agent::getType() const {
  return m_settings.m_type;
}