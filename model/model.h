#pragma once

class Kernel {
  void scanAgentsFolder();
  void updateMetrics();
  void logMetrics(const std::string& metrics);
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
