#pragma once

#include <QDir>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QObject>
#include <QStringList>

class Watcher : public QObject {
  Q_OBJECT

 public:
  explicit Watcher(const QString & path, QObject *parent = nullptr);
  virtual ~Watcher();

 signals:
  void FileDetected(QString conf, QString lib);

 public slots:
  void directoryChanged(const QString &path);

 private slots:
  void fileChanged(const QString &path);
  void directoryChanged(const QString &path);

 private:
  QFileSystemWatcher *m_watcher;
  QString m_root;
};
