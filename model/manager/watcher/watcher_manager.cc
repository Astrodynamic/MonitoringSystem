#include "watcher_manager.h"

Watcher::Watcher(const QString & path, QObject *parent)
  : QObject(parent)
  , m_watcher(new QFileSystemWatcher(this))
  , m_root{path} {
  m_watcher->addPath(m_root);

  connect(m_watcher, SIGNAL(directoryChanged(QString)), this, SLOT(directoryChanged(QString)));
  connect(m_watcher, SIGNAL(fileChanged(QString)), this, SLOT(fileChanged(QString)));
}

Watcher::~Watcher() {
  delete m_watcher;
}

void Watcher::setRoot(const QString &path) {
  m_watcher->removePath(m_root);
  m_watcher->addPath(path);
  m_root = path;
}

void Watcher::fileChanged(const QString &path) {
  QFileInfo fileInfo(path);

  if (fileInfo.isFile() && fileInfo.fileName() == "settings.conf") {
    QDir dir(fileInfo.path());
    QStringList entries = dir.entryList(QStringList() << "*.so");
    for (const QString& entry : entries) {
      QString libPath = fileInfo.path() + "/" + entry;
      QFileInfo libInfo(libPath);
      if (libInfo.exists() && libInfo.isFile()) {
        emit FileDetected(path, libPath);
        m_watcher->removePath(fileInfo.path());
        break;
      }
    }
  } else if (fileInfo.isFile() && fileInfo.suffix() == "so") {
    QString confPath = fileInfo.path() + "/settings.conf";
    QFileInfo confInfo(confPath);
    if (confInfo.exists() && confInfo.isFile()) {
      emit FileDetected(confPath, path);
      m_watcher->removePath(fileInfo.path());
    }
  }
}

void Watcher::directoryChanged(const QString &path) {
  m_watcher->addPath(path);
}
