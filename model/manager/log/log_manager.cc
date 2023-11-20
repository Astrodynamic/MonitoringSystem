#include "log_manager.h"

LogManager::LogManager(QString path, QObject *parent)
  : QObject(parent)
  , m_path(path)
  , m_buffer_size(100) {}

LogManager::~LogManager() {
  Flush();
}

auto LogManager::BufferSize(qsizetype size) -> void {
  m_buffer_size = size;
}

auto LogManager::Write(const QString &message, LogLevel level) -> void {
  static const QHash<LogLevel, QString> map {
    { LogLevel::kDEBUG, "DEBUG" },
    { LogLevel::kINFO, "INFO" },
    { LogLevel::kWARNING, "WARNING" },
    { LogLevel::kERROR, "ERROR" }
  };

  static const int field_width = 8;

  QString lvl = QString("%1").arg(map.value(level), field_width);

  QDateTime now = QDateTime::currentDateTime();
  QString time = now.toString("yy-MM-dd HH:mm:ss");

  m_buffer.enqueue(lvl + '|' + time  + '|' + message);
  emit logsChanged();

  Flush(m_buffer_size);
}

auto LogManager::Read() const -> QStringList {
  QStringList entries;
  int entries_count = qMin(m_buffer.size(), static_cast<int>(m_buffer_size));
  for (int i = 0; i < entries_count; ++i) {
    entries.append(m_buffer.at(i));
  }

  return entries;
}

auto LogManager::Flush(qsizetype leave) -> void {
  if (m_buffer.size() > leave) {
    QDateTime now = QDateTime::currentDateTime();
    QFile file(m_path + QDir::separator() + QString("log_%1.txt").arg(now.toString("yyyy-MM-dd")));
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
      QTextStream m_stream(&file);
      m_stream.setEncoding(QStringConverter::Utf8);
      while (m_buffer.size() > leave) {
        m_stream << m_buffer.dequeue() << '\n';
      }
      m_stream.flush();
    }
    file.close();
  }
}
