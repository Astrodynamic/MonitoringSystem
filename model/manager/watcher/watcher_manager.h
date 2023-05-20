#pragma once

#include <QDir>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QObject>
#include <QStringList>

class WatcherManager : public QObject {
  Q_OBJECT

 public:
  explicit WatcherManager(const QString & path, QObject *parent = nullptr);
  virtual ~WatcherManager();

 signals:
  void FileDetected(QString conf, QString lib);

 public slots:
  void setRoot(const QString &path);

 private slots:
  void directoryChanged(const QString &path);

 private:
  QFileSystemWatcher *m_watcher;
  QString m_root;
};
