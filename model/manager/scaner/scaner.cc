#include "scaner.h"

Scaner::Scaner(QObject *parent)
    : QObject{parent} {
    connect(&m_watcher, SIGNAL(directoryChanged(const QString &)), this, SLOT(VerificateFile(const QString &)));
}

void Scaner::AddDirectory(QString &path) {
    m_watcher.addPath(path);
}

QHash<QString, Metric> Scaner::ReadMetrics(QVariantList metricsList) {
    QHash<QString, Metric> metricHash;
    foreach(QVariant metricVariant, metricsList) {
        QMap<QString, QVariant> metricMap = metricVariant.toMap();
        QString metricName = metricMap["name"].toString();
        Metric metric = {metricName,
                         ReadComparisonOperator(metricMap["comparison"].toString()),
                         metricMap["critical_value"].toInt()};
        metricHash.insert(metricName, metric);
    }
    return metricHash;
}

ComparisonOperator Scaner::ReadComparisonOperator(QString operatorName) {
    if (operatorName == ">=") {
        return ComparisonOperator::kGreaterThanOrEqualTo;
    } else if (operatorName == "<=") {
        return ComparisonOperator::kLessThanOrEqualTo;
    } else if (operatorName == ">") {
        return ComparisonOperator::kGreaterThan;
    } else if (operatorName == "<") {
        return ComparisonOperator::kLessThan;
    }
    return ComparisonOperator::kEqualTo;
}

void Scaner::VerificateFile(QString new_file_way) {
    if (new_file_way.endsWith(".conf") && QFile::exists(new_file_way.chopped(4).append("so"))) {
        CreateAgentSetting(new_file_way);
    } else if (new_file_way.endsWith(".so") && QFile::exists(new_file_way.chopped(2).append(".conf"))) {
        CreateAgentSetting(new_file_way.chopped(2).append(".conf"));
    }
}

void Scaner::CreateAgentSetting(QString new_conf_file) {
    QSettings conf_file(new_conf_file, QSettings::IniFormat);
    AgentSettings new_settings;
    new_settings.m_enabled = conf_file.value("enabled", false).toBool();
    new_settings.m_name = conf_file.value("name", "Unknow").toString();
    new_settings.m_type = conf_file.value("type", "Unknow").toString();
    new_settings.m_interval = conf_file.value("interval", 1).toTime();
    new_settings.m_config = QFileInfo(new_conf_file);
    new_settings.m_metrics = ReadMetrics(conf_file.value("metrics").toList());
    emit MakeAgent(new_settings);
}

