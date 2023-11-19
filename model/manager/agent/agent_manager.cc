#include "agent_manager.h"

AgentManager::AgentManager(QObject *parent) : QAbstractListModel(parent) {
    m_timer.start(1000);

    connect(&m_timer, &QTimer::timeout, [this]() {
        for (qsizetype idx{}; idx < m_data.size(); ++idx) {
            auto index = createIndex(idx, 0);
            auto &setting = m_data[idx].second->Settings();
            if (setting.m_enabled) {
                emit dataChanged(index, index, QVector<int>() << kTimerRole);
            } else {
                setting.m_timer.start();
            }
        }
    });
}

AgentManager::~AgentManager() {
  removeRows(0, m_data.size());
}

auto AgentManager::rowCount(const QModelIndex &parent) const -> int {
  if (parent.isValid()) return 0;

  return m_data.size();
}

auto AgentManager::data(const QModelIndex &index, int role) const -> QVariant {
  if (!index.isValid()) return QVariant();

  AgentSettings &settings = m_data.at(index.row()).second->Settings();

  if (role == kEnabledRole) {
    return QVariant::fromValue(settings.m_enabled);
  } else if (role == kNameRole) {
    return QVariant::fromValue(settings.m_name);
  } else if (role == kTypeRole) {
    return QVariant::fromValue(settings.m_type);
  } else if (role == kIntervalRole) {
    return QVariant::fromValue(settings.m_interval);
  } else if (role == kConfigRole) {
    return QVariant::fromValue(settings.m_config);
  } else if (role == kTimerRole) {
    return QVariant::fromValue(QTime(0, 0).addMSecs(settings.m_timer.elapsed()));
  } else if (role == kMetricsRole) {
    return QVariant::fromValue(settings.m_metrics);
  }
  return QVariant();
}

auto AgentManager::roleNames() const -> QHash<int, QByteArray> {
  static const QHash<int, QByteArray> roles{
    {kEnabledRole, "enabled"},
    {kNameRole, "name"},
    {kTypeRole, "type"},
    {kIntervalRole, "interval"},
    {kConfigRole, "config"},
    {kTimerRole, "timer"},
    {kMetricsRole, "metrics"}
  };

  return roles;
}

auto AgentManager::setData(const QModelIndex &index, const QVariant &value, int role) -> bool {
  AgentSettings &settings = m_data[index.row()].second->Settings();
  if (role == kEnabledRole) {
    settings.m_enabled = value.toBool();
  } else if (role == kNameRole) {
    settings.m_name = value.toString();
  } else if (role == kTypeRole) {
    settings.m_type = value.toString();
  } else if (role == kIntervalRole) {
    settings.m_interval->start(value.toInt());
  } else if (role == kConfigRole) {
    settings.m_config = value.value<QFileInfo>();
  } else if (role == kTimerRole) {
    settings.m_timer = value.value<QElapsedTimer>();
  } else if (role == kMetricsRole) {
    settings.m_metrics = value.value<QHash<QString, Metric>>();
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
    m_data.at(row).first->unload();
    m_data.removeAt(row);
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

auto AgentManager::config(int index) -> QString {
    if (index < 0 || index > m_data.size()) {
        return "";
    }

    QString path = m_data[index].second->Settings().m_config.absoluteFilePath();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return file.errorString();
    }
    return file.readAll();
}

auto AgentManager::config(int index, QString json) -> void {
    if (index >= 0 && index < m_data.size()) {
        auto &settings = m_data[index].second->Settings();
        QString path = settings.m_config.absoluteFilePath();
        QFile file(path);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << json;
        }
        file.close();

        emit updateConfiguration(path, settings);
        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
    }
}
