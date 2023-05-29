#pragma once

#include <QDebug>
#include <QFile>
#include <QObject>
#include <QTextStream>

class LogManager : public QObject {
  Q_OBJECT

 public:
  explicit LogManager(QObject* parent = nullptr);
  ~LogManager();

  auto Write(const QString& message) -> void;

 private:
  QFile m_file;
  QTextStream m_stream;
};
