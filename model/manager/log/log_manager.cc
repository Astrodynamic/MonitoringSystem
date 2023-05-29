#include "log_manager.h"

LogManager::LogManager(QObject *parent) : QObject(parent) {
  m_file.setFileName("logfile.txt");
  if (!m_file.open(QIODevice::Append | QIODevice::Text)) {
    qDebug() << "Failed to open log file";
  }
}

LogManager::~LogManager() {}