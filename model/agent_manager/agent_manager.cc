#include "agent_manager.h"

AgentManager::AgentManager(QObject *parent) : QAbstractListModel(parent) {
  m_data.append("old");
  m_data.append("another old");
}

int AgentManager::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;

  return m_data.size();
}

QVariant AgentManager::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  switch (role) {
    case ColorRole:
      return QVariant(index.row() < 2 ? "orange" : "skyblue");
    case TextRole:
      return m_data.at(index.row());
    default:
      return QVariant();
  }
}

QHash<int, QByteArray> AgentManager::roleNames() const {
  QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
  roles[ColorRole] = "color";
  roles[TextRole] = "text";

  return roles;
}

bool AgentManager::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (data(index, role) != value) {
    switch (role) {
    case ColorRole:
        return false;
    case TextRole:
        m_data[index.row()] = value.toString();
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
  if (!index.isValid())
    return Qt::NoItemFlags;

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

void AgentManager::add() {
  beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
  m_data.append("new");
  endInsertRows();

  m_data[0] = QString("Size: %1").arg(m_data.size());
  QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
  emit dataChanged(index, index);
}