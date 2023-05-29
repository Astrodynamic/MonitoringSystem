#pragma once

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QIODevice>
#include <QObject>
#include <QQueue>
#include <QTextStream>
#include <QTimer>
#include <QtCore>

class LogManager : public QObject {
  Q_OBJECT

 public:
  enum class LogLevel { kDEBUG = 0, kINFO, kWARNING, kERROR };

  explicit LogManager(QString path, QObject* parent = nullptr);
  virtual ~LogManager();

  auto Write(const QString& message, LogLevel level = LogLevel::kDEBUG) -> void;
  auto Read(qsizetype count = 20) const -> QStringList;

 private slots:
  auto CreateFile() -> void;

 private:
  QFile m_file;
  QTimer m_timer;
  QString m_path;
  unsigned m_max_size;
  QTextStream m_stream;
  QQueue<QString> m_buffer;

  auto Flush() -> void;
};
