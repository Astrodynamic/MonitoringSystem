#pragma once

class Kernel : public QObject {
    Q_OBJECT
public:
    explicit Kernel(AgentManager* agentManager, QObject* parent = nullptr);

    void scanAgentsFolder();
    Q_INVOKABLE void updateMetrics();
    Q_INVOKABLE void logMetrics(const QString& metrics);

    signals:
  void metricsUpdated(const QString& metrics);
  void metricsLogged(const QString& logEntry);

private:
    AgentManager* m_agentManager;
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