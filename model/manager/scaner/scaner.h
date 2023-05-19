#ifndef SCANER_H
#define SCANER_H

#include <QObject>
#include <QSettings>
#include <QFileSystemWatcher>

#include "agent_settings.h"

class Scaner : public QObject
{
    Q_OBJECT
public:
    explicit Scaner(QObject *parent = nullptr);
    void AddDirectory(QString &path);
protected:

private:
    QFileSystemWatcher m_watcher;
    QSet<QString> m_conf_file_list;
    QHash<QString, Metric> ReadMetrics(QVariantList metricsList);
    ComparisonOperator ReadComparisonOperator(QString operatorName);
private slots:
    void VerificateFile(QString new_file_way);
    void CreateAgentSetting(QString new_conf_file);

signals:
    void MakeAgent(AgentSettings);
};

#endif // SCANER_H
