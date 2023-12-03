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
  Q_PROPERTY(QStringList logs READ Read NOTIFY logsChanged FINAL)

 public:
  enum class LogLevel { kDEBUG = 0, kINFO, kWARNING, kERROR };

  explicit LogManager(QString path, QObject* parent = nullptr);
  virtual ~LogManager();

  auto BufferSize(qsizetype size) -> void;
  auto Read() const -> QStringList;

 public slots:
  auto Write(const QString& message, LogLevel level = LogLevel::kDEBUG) -> void;

 signals:
  void logsChanged();

 private:
  QString m_path;
  unsigned m_buffer_size;
  QQueue<QString> m_buffer;

  auto Flush(qsizetype leave = 0) -> void;
};
