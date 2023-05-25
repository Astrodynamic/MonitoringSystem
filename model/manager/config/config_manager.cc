#include "config_manager.h"

ConfigurationManager::ConfigurationManager(QObject *parent) : QObject(parent) {}

ConfigurationManager::~ConfigurationManager() {}

bool ConfigurationManager::loadConfiguration(const QString &path, AgentSettings &settings) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Не удалось открыть файл:" << file.errorString();
    return false;
  }

  const QJsonDocument json = QJsonDocument::fromJson(QByteArray(file.readAll()));
  if (json.isNull()) {
    qDebug() << "Ошибка при разборе JSON-документа.";
    return false;
  }

  file.close();

  QJsonObject root = json.object();

  settings.m_enabled = root.value("enabled").toBool();
  settings.m_name = root.value("name").toString();
  settings.m_type = root.value("type").toString();

  settings.m_interval = QTime(0, 0).addSecs(root.value("interval").toInt());

  QJsonArray metrics = root.value("metrics").toArray();

  static const QMap<QString, ComparisonOperator> op = {
      {">=", ComparisonOperator::kGreaterThanOrEqualTo},
      {">", ComparisonOperator::kGreaterThan},
      {"<=", ComparisonOperator::kLessThanOrEqualTo},
      {"<", ComparisonOperator::kLessThan},
      {"==", ComparisonOperator::kEqualTo}
  };

  for (const QJsonValue &metric : metrics) {
    const QJsonObject metricObject = metric.toObject();
    settings.m_metrics[metricObject.value("name").toString()] =
        Metric{metricObject.value("value").toVariant(),
               op[metricObject.value("comparison").toString()],
               metricObject.value("critical_value").toVariant()};
  }

  return true;
}
