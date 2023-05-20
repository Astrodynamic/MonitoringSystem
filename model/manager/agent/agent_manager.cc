#include "agent_manager.h"

AgentManager::AgentManager(QObject *parent) : QAbstractListModel(parent) {
}

int AgentManager::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  return m_data.size();
}

QVariant AgentManager::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  if (role == kNameRole) {
    return QVariant::fromValue(m_data.at(index.row())->getSettings().m_name);
  } else if (role == kTypeRole) {
    return QVariant::fromValue(m_data.at(index.row())->getSettings().m_type);
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
        m_data[index.row()]->getSettings().m_name = value.toString();
      case kTypeRole:
        m_data[index.row()]->getSettings().m_type = value.toString();
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
  QLibrary myLibrary("/opt/goinfre/werewolf/Documents/github/MonitoringSystem/agents/cpu_agent/libcpu_agent");
  if (!myLibrary.load()) {
    qDebug() << "Ошибка при загрузке библиотеки";
    qDebug() << myLibrary.errorString();
    return false;
  }

  using fn = Agent* (*)(const AgentSettings&);
  fn newbie = reinterpret_cast<fn>(myLibrary.resolve("create"));
  if (!newbie) {
    qDebug() << "Ошибка при регистрации агента";
    qDebug() << myLibrary.errorString();
    return false;
  }

  Agent * agent = newbie(settings);
  if (!agent) {
    qDebug() << "Ошибка при создании агента";
    return false;
  }

  beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
  m_data.push_back(agent);
  endInsertRows();
/////////////////////////////////////////////////////////
  auto way = settings.m_config.path().toStdString();

  void *handle = dlopen(way.c_str(), RTLD_LAZY);
  if (!handle) {
      qDebug() << "Error loading library: " << dlerror();
      return false;
  }

  // Получить указатель на функцию-фабрику
  typedef Agent *(*create)();
  create createFunc = (create) dlsym(handle, "create");
  if (!createFunc) {
      qDebug() << "Error getting symbol: " << dlerror();
      dlclose(handle);
      return false;
  }

  // Создать экземпляр класса
  Agent *obj = createFunc();

  // Использовать объект ...
  obj->getMetrics();
  // Выгрузить библиотеку
  dlclose(handle);

  return true;
}
