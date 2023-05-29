#include "log_manager.h"

LogManager::LogManager(QString path, QObject *parent)
  : QObject(parent)
  , m_timer(this) 
  , m_path(path)
  , m_max_size(100) {}

LogManager::~LogManager() {
  Flush();
}

auto LogManager::BufferSize(qsizetype size) -> void {
  m_buffer_size = size;
}

auto LogManager::Write(const QString &message, LogLevel level) -> void {
  static const QHash<LogLevel, QString> map {
    { LogLevel::kDEBUG, "DEBUG:" },
    { LogLevel::kINFO, "INFO:" },
    { LogLevel::kWARNING, "WARNING:" },
    { LogLevel::kERROR, "ERROR:" }
  };

  static const int field_width = 10;

  QString lvl = QString("%1").arg(map.value(level), field_width);
  m_buffer.enqueue(lvl + message);

  Flush(m_buffer_size);
}

auto LogManager::Read() const -> QStringList {
  QStringList entries;
  for (int i = 0; i <= m_buffer_size; ++i) {
    entries.append(m_buffer.at(i));
  }

  return entries;
}

auto LogManager::Flush(qsizetype leave) -> void {
  if (m_buffer.size() > leave) {
    QFile file(m_path + QDir::separator() + QString("log_%1.txt").arg(now.toString("yyyy-MM-dd")));
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
      QTextStream m_stream(&file);
      m_stream.setEncoding(QStringConverter::Utf8);
      while (m_buffer.size() > leave) {
        m_stream << m_buffer.dequeue() << '\n';
        m_stream.flush();
      }
    }
    file.close();
  }
}