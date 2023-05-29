#include "log_manager.h"

LogManager::LogManager(QString path, QObject *parent)
  : QObject(parent)
  , m_timer(this) 
  , m_path(path)
  , m_max_size(100) {
  QObject::connect(&m_timer, &QTimer::timeout, this, &LogManager::CreateFile);
  m_timer.start();
}

LogManager::~LogManager() {
  Flush();
}

auto LogManager::Write(const QString &message, LogLevel level) -> void {
  m_buffer.enqueue(message);

  static const QHash<LogLevel, QString> map {
    { LogLevel::kDEBUG, "DEBUG:" },
    { LogLevel::kINFO, "INFO:" },
    { LogLevel::kWARNING, "WARNING:" },
    { LogLevel::kERROR, "ERROR:" }
  };

  static const int field_width = 10;

  if (m_buffer.size() > m_max_size) {
    QString lvl = QString("%1").arg(map.value(level), field_width);
    m_stream << lvl << m_buffer.dequeue() << '\n';
    m_stream.flush();
  }
}

auto LogManager::Read(qsizetype count) const -> QStringList {
  QStringList entries;
  int s_idx = qMax(0, m_buffer.size() - count);
  int e_idx = m_buffer.size() - 1;

  for (int i = s_idx; i <= e_idx; ++i) {
    entries.append(m_buffer.at(i));
  }

  return entries;
}

auto LogManager::CreateFile() -> void {
  QDateTime now = QDateTime::currentDateTime();

  QDateTime midnight = now;
  midnight.setTime(QTime(0, 0));
  if (now.time() > QTime(0, 0)) {
    midnight = midnight.addDays(1);
  }
  qint64 ms = now.msecsTo(midnight);

  Flush();

  m_file.setFileName(m_path + QDir::separator() + QString("log_%1.txt").arg(now.toString("yyyy-MM-dd")));
  if (m_file.open(QIODevice::Append | QIODevice::Text)) {
    m_stream.setDevice(&m_file);
    m_stream.setEncoding(QStringConverter::Utf8);
  }

  m_timer.start();
}

auto LogManager::Flush() -> void {
  if (m_file.isOpen()) {
    while (m_buffer.size() > 0) {
      m_stream << m_buffer.dequeue() << '\n';
      m_stream.flush();
    }
  }
  m_file.close();
}