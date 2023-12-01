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

auto WatcherManager::setRoot(const QString &path) -> void {
  if (m_root != path) {
    QDir tmp;
    if (!tmp.exists(path)) {
       tmp.mkpath(path);
    }

    m_watcher->removePath(m_root);
    m_watcher->addPath(path);
    m_root = path;

    QDir dir(m_root);
    QStringList entries = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &entry : entries) {
      directoryChanged(path + "/" + entry);
    }
  }
}

auto WatcherManager::directoryChanged(const QString &path) -> void {
  QDir dir(path);
  if (path == m_root) {
    QStringList entries = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QString &entry : entries) {
      QString dir_path = path + "/" + entry;
      if (!m_watcher->directories().contains(dir_path)) {
        m_watcher->addPath(dir_path);
      }
    }
  } else {
    QFileInfoList c_files = dir.entryInfoList(QStringList() << "*.json", QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList l_files = dir.entryInfoList(QStringList() << "*.so", QDir::Files | QDir::NoDotAndDotDot);

    if (!c_files.isEmpty() && !l_files.isEmpty()) {
      emit FileDetected(c_files.first().absoluteFilePath(), l_files.first().absoluteFilePath());
      m_watcher->removePath(path);
    }
  }
}
