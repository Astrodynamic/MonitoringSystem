#pragma once

#include <QObject>

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


class Agent {
 public:
  virtual void updateMetrics() = 0;
};

class CpuLoadAgent : public Agent {
 public:
  void updateMetrics() override {
    // Сбор метрик CPU
  }
};

class MemoryAgent : public Agent {
 public:
  void updateMetrics() override {
    // Сбор метрик памяти
  }
};

class NetworkAgent : public Agent {
 public:
  void updateMetrics() override {
    // Сбор метрик сети
  }
};

class LogManager {
 public:
  void createLogFile(const std::string& fileName) {
    // Создание нового лог-файла с заданным именем
  }

  void writeMetricsToLog(const std::string& metrics) {
    // Запись метрик в лог-файл
  }

  std::vector<std::string> getLastLogLines(int lineCount) {
    // Получение последних N строк из лог-файла
  }
};

#include <QSettings>

class ConfigurationManager {
 public:
  // Сохранение конфигурации агента
  void saveAgentConfiguration(const QString& agentName,
                              const QString& configFile) {
    QSettings settings(configFile, QSettings::IniFormat);

    // Сохранение параметров агента
    settings.setValue("Agent/Name", agentName);
    settings.setValue("Agent/Type", agentType);
    settings.setValue("Agent/Metrics", metricList);
    // ... сохранение остальных параметров

    settings.sync();  // Сохранение изменений в файле
  }

  // Загрузка конфигурации агента
  void loadAgentConfiguration(const QString& configFile) {
    QSettings settings(configFile, QSettings::IniFormat);

    // Загрузка параметров агента
    QString agentName = settings.value("Agent/Name").toString();
    QString agentType = settings.value("Agent/Type").toString();
    QStringList metricList = settings.value("Agent/Metrics").toStringList();
    // ... загрузка остальных параметров
  }

  void updateAgentConfiguration(const std::string& agentName,
                                const std::string& configuration) {
    // Обновление конфигурации агента
  }
};

class NotificationManager {
 public:
  void sendTelegramNotification(const std::string& message) {
    // Отправка уведомления в Telegram
  }

  void sendEmailNotification(const std::string& recipient,
                             const std::string& subject,
                             const std::string& message) {
    // Отправка уведомления на электронную почту
  }
};
