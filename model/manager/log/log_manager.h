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

  auto BufferSize(qsizetype size) -> void;

  auto Write(const QString& message, LogLevel level = LogLevel::kDEBUG) -> void;
  auto Read() const -> QStringList;

 private:
  QString m_path;
  unsigned m_buffer_size;
  QQueue<QString> m_buffer;

  auto Flush(qsizetype leave = 0) -> void;
};
