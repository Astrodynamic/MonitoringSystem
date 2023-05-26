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
  auto FileDetected(QString conf, QString lib) -> void;

 public slots:
  auto setRoot(const QString &path) -> void;

 private slots:
  auto directoryChanged(const QString &path) -> void;

 private:
  QFileSystemWatcher *m_watcher;
  QString m_root;
};
