#pragma once

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