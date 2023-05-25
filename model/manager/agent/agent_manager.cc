#include "agent_manager.h"

#include <QtPlugin>

AgentManager::AgentManager(QObject *parent) : QAbstractListModel(parent) {
}

int AgentManager::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  return m_data.size();
}

QVariant AgentManager::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  AgentSettings &settings = m_data.at(index.row())->getSettings();

  if (role == kNameRole) {
    return QVariant::fromValue(settings.m_name);
  } else if (role == kTypeRole) {
    return QVariant::fromValue(settings.m_type);
  }
  return QVariant();
}

QHash<int, QByteArray> AgentManager::roleNames() const {
  static QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
  roles[kNameRole] = "name";
  roles[kTypeRole] = "type";

  return roles;
}

bool AgentManager::setData(const QModelIndex &index, const QVariant &value, int role) {
  AgentSettings &settings = m_data[index.row()]->getSettings();
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

Qt::ItemFlags AgentManager::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;

  return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool AgentManager::removeRows(int row, int count, const QModelIndex &parent) {
  if (!parent.isValid()) {
    return false;
  }

  beginRemoveRows(parent, row, row + count - 1);

  for (int i = 0; i < count; ++i) {
    delete m_data.at(row + i);
    m_data.removeAt(row + i);
  }
  endRemoveRows();

  return true;
}

bool AgentManager::registerAgent(AgentSettings &settings) {
    QString libName = "/opt/goinfre/ajhin/github/MonitoringSystem/testF/build-cpu_agent-Desktop_x86_darwin_generic_mach_o_64bit-Debug/libcpu_agent.dylib";


    QPluginLoader plugin(libName);

    if (!plugin.load()) {
        qDebug() << "Плагин не загружен";
    }

    Agent* pluginInterface = qobject_cast<Agent *>(plugin.instance());
    if (pluginInterface) {
        pluginInterface->getMetrics();
    }

  //beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
  //m_data.push_back(agent);
  //endInsertRows();

    return true;
}
