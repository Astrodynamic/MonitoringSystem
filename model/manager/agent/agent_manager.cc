#include "agent_manager.h"

#include <QtPlugin>

AgentManager::AgentManager(QObject *parent) : QAbstractListModel(parent) {}

AgentManager::~AgentManager() {}

auto AgentManager::rowCount(const QModelIndex &parent) const -> int {
  if (parent.isValid()) return 0;

  return m_data.size();
}

auto AgentManager::data(const QModelIndex &index, int role) const -> QVariant {
  if (!index.isValid()) return QVariant();

  AgentSettings &settings = m_data.at(index.row()).second->Settings();

  if (role == kNameRole) {
    return QVariant::fromValue(settings.m_name);
  } else if (role == kTypeRole) {
    return QVariant::fromValue(settings.m_type);
  }
  return QVariant();
}

auto AgentManager::roleNames() const -> QHash<int, QByteArray> {
  static QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
  roles[kNameRole] = "name";
  roles[kTypeRole] = "type";

  return roles;
}

auto AgentManager::setData(const QModelIndex &index, const QVariant &value, int role) -> bool {
  AgentSettings &settings = m_data[index.row()].second->Settings();
  if (role == kNameRole) {
    settings.m_name = value.toString();
  } else if (role == kTypeRole) {
    settings.m_type = value.toString();
  } else {
    return false;
  }
  emit dataChanged(index, index, QVector<int>() << role);
  return true;
}

auto AgentManager::flags(const QModelIndex &index) const -> Qt::ItemFlags {
  if (!index.isValid()) return Qt::NoItemFlags;

  return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

auto AgentManager::removeRows(int row, int count, const QModelIndex &parent) -> bool {
  if (!parent.isValid()) {
    return false;
  }

  beginRemoveRows(parent, row, row + count - 1);

  for (int i = 0; i < count; ++i) {
    m_data.removeAt(row + i);
  }
  endRemoveRows();

  return true;
}

auto AgentManager::registerAgent(const QString &path, AgentSettings &settings) -> bool {
  QSharedPointer<QLibrary> library(new QLibrary(path));
  if (!library->load()) {
    qDebug() << "Failed to load library:" << library->errorString();
    return false;
  }

  using fn = Agent *(*)(const AgentSettings settings);
  fn __create = (fn)library->resolve("__create");
  if (!__create) {
    qDebug() << "Failed to resolve __create function";
    return false;
  }

  beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
  m_data.push_back({library, QSharedPointer<Agent>(__create(settings))});
  endInsertRows();

  return true;
}
