#include "config_manager.h"

ConfigurationManager::ConfigurationManager(QObject *parent) : QObject(parent) {}

ConfigurationManager::~ConfigurationManager() {}

bool ConfigurationManager::loadConfiguration(QString & path, AgentSettings &settings) {
  QSettings config(path, QSettings::IniFormat);
  
  settings.m_enabled = config.value("enabled", true).toBool();
  settings.m_name = config.value("name").toString();
  settings.m_type = config.value("type").toString();
  settings.m_interval = QTime::fromString(config.value("interval").toString(), "s");
  
  QStringList metricConfigs = config.value("metrics").toStringList();
  for (const QString &metricConfig : metricConfigs) {
    QJsonDocument metricDoc = QJsonDocument::fromJson(metricConfig.toUtf8());
    QJsonObject metricObj = metricDoc.object();

    QString metricName = metricObj.value("name").toString();
    QString comparisonOperator = metricObj.value("comparison").toString();
    QString criticalValue = metricObj.value("critical_value").toString();

    Metric metric;
    metric.op = stringToComparisonOperator(comparisonOperator);
    metric.comparisonValue = criticalValue.toDouble();
    settings.m_metrics.insert(metricName, metric);
  }

  return true;
}