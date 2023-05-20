#include "watcher_manager.h"

WatcherManager::WatcherManager(const QString & path, QObject *parent)
  : QObject(parent)
  , m_watcher(new QFileSystemWatcher(this))
  , m_root{path} {
  m_watcher->addPath(m_root);

  connect(m_watcher, &QFileSystemWatcher::directoryChanged, this, &WatcherManager::directoryChanged);
}

WatcherManager::~WatcherManager() {
  delete m_watcher;
}

void WatcherManager::setRoot(const QString &path) {
  m_watcher->removePath(m_root);
  m_watcher->addPath(path);
  m_root = path;
}

void WatcherManager::directoryChanged(const QString &path) {
  qDebug() << "Directory changed" << path;

  if (path == m_root) {
    QDir dir(path);
    QStringList entries = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QString &entry : entries) {
      QString dir_path = path + "/" + entry;
      if (!m_watcher->directories().contains(dir_path)) {
        m_watcher->addPath(dir_path);
      }
    }
  } else {
    QDir dir(path);
    QFileInfoList c_files = dir.entryInfoList(QStringList() << "*.conf", QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList l_files = dir.entryInfoList(QStringList() << "*.so", QDir::Files | QDir::NoDotAndDotDot);

    if (!c_files.isEmpty() && !l_files.isEmpty()) {
      emit FileDetected(c_files.at(0).absoluteFilePath(), l_files.at(0).absoluteFilePath());
      m_watcher->removePath(path);
    }
  }
}
