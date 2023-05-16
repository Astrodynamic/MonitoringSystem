#pragma once


#include <QList>
#include "agent.h"

class AgentManager : public QAbstractListModel {
    Q_OBJECT
public:
    enum AgentRoles {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        // Дополнительные роли агента
    };

    AgentManager(QObject *parent = nullptr);

    void addAgent(const Agent &agent);
    void removeAgent(int index);
    Agent agentAt(int index) const;

    // Реализация методов QAbstractListModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Дополнительные методы для управления агентами
    void updateMetrics();
    void logMetrics(const std::string& metrics);

private:
    QList<Agent> agents;
};

void AgentManager::updateMetrics() {
    // Обновление метрик всех агентов
    for (Agent& agent : agents) {
        agent.updateMetrics();
    }

    // TODO: выполните дополнительные действия по обновлению метрик
}

void AgentManager::logMetrics(const std::string& metrics) {
    // Запись метрик в лог-файл
    // TODO: выполните запись метрик в лог-файл

    // TODO: выполните дополнительные действия по записи метрик
}

#include <QList>
#include "agent.h"

class AgentsModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum AgentRoles {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        // Дополнительные роли агента
    };

    AgentsModel(QObject* parent = nullptr);

    void addAgent(const Agent& agent);
    void removeAgent(int index);
    Agent agentAt(int index) const;

    // Реализация методов QAbstractListModel
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
};

class AgentManager : public QObject {
    Q_OBJECT
public:
    AgentManager(QObject* parent = nullptr);

    Q_INVOKABLE void scanAgentsFolder();
    Q_INVOKABLE void updateMetrics();
    Q_INVOKABLE void logMetrics(const QString& metrics);

    AgentsModel* agentsModel() const;

private:
    AgentsModel* m_agentsModel;
};

class Kernel : public QObject {
    Q_OBJECT
public:
    explicit Kernel(AgentManager* agentManager, QObject* parent = nullptr);

    Q_INVOKABLE void updateMetrics();
    Q_INVOKABLE void logMetrics(const QString& metrics);

private:
    AgentManager* m_agentManager;
};


class Kernel : public QObject {
  Q_OBJECT

public:
  void scanAgentsFolder();
  void updateMetrics();
  void logMetrics(const std::string& metrics);

signals:
  void metricsUpdated(const QString& metrics);
  void metricsLogged(const QString& logEntry);
};

void Kernel::updateMetrics() {
  // Обновление метрик
  QString metrics = "cpu: 80%, ram: 50%, disk: 60%";
  
  // Генерация сигнала о обновлении метрик
  emit metricsUpdated(metrics);
}

void Kernel::logMetrics(const std::string& metrics) {
  // Запись метрик в лог-файл
  QString logEntry = QString::fromStdString(metrics);

  // Генерация сигнала о записи метрик в лог-файл
  emit metricsLogged(logEntry);
}

#include <QAbstractListModel>
#include <QList>
#include "agent.h" // Подключение заголовочного файла с определением класса агента

class AgentsModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum AgentRoles {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        // Дополнительные роли агента
    };

    AgentsModel(QObject *parent = nullptr);

    void addAgent(const Agent &agent);
    void removeAgent(int index);
    Agent agentAt(int index) const;

    // Реализация методов QAbstractListModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
};