#include "agent_manager.h"

AgentManager::AgentManager(QObject *parent) : QAbstractListModel(parent) {
  m_data.append(Agent());
  m_data.append(Agent());
}

int AgentManager::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  return m_data.size();
}

QVariant AgentManager::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  if (role == kNameRole) {
    return QVariant::fromValue(m_data.at(index.row()).getSettings().m_name);
  } else if (role == kTypeRole) {
    return QVariant::fromValue(m_data.at(index.row()).getSettings().m_type);
  }
  return QVariant();
}

QHash<int, QByteArray> AgentManager::roleNames() const {
  QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
  roles[kNameRole] = "name";
  roles[kTypeRole] = "type";

  return roles;
}

bool AgentManager::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (data(index, role) != value) {
    switch (role) {
      case kNameRole:
        m_data[index.row()].getSettings().m_name = value.toString();
      case kTypeRole:
        m_data[index.row()].getSettings().m_type = value.toString();
        break;
      default:
        return false;
    }
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
  }
  return false;
}

Qt::ItemFlags AgentManager::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;

  return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool AgentManager::insertRows(int row, int count, const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endInsertRows();
}

bool AgentManager::removeRows(int row, int count, const QModelIndex &parent) {
  beginRemoveRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endRemoveRows();
}
