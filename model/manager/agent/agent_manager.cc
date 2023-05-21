#include "agent_manager.h"
#include <QObject>
#include <QLibrary>

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
    QString libName = "/opt/goinfre/ajhin/github/MonitoringSystem/testF/build-lib_cpu_agent-Desktop_x86_darwin_generic_mach_o_64bit-Debug/liblib_cpu_agent.dylib";

QLibrary myLibrary(libName);
  if (!myLibrary.load()) {
    qDebug() << "Ошибка при загрузке библиотеки";
    qDebug() << myLibrary.errorString();
    return false;
  }


  using fn = Agent* (*)(const AgentSettings&);
  fn newbie = reinterpret_cast<fn>(myLibrary.resolve("_ZN13Lib_cpu_agent8sayHelloEv"));
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



//


//    auto way = libName.toStdString();

//    void* handle = dlopen(way.c_str(), RTLD_LAZY);

//    if (!handle) { // проверка ошибок при открытии библиотеки
//        qDebug() << "Cannot open library: " << dlerror() << '\n';
//        return 1;
//    }





//    void (*sayHello)() = reinterpret_cast<void (*)()>(dlsym(handle, "_ZN13Lib_cpu_agent8sayHelloEv"));

//    if (!sayHello) { // проверка ошибок при получении указателя на функцию
//        qDebug() <<  "Cannot load symbol 'sayHello': " << dlerror() << '\n';
//        dlclose(handle);
//        return 1;
//    }

//    sayHello();
//    // закрываем динамическую библиотеку
//    dlclose(handle);


  return true;
}
