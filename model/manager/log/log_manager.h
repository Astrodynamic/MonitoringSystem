#pragma once

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class LogManager : public QObject {
  Q_OBJECT

 public:
  explicit LogManager(QObject *parent = nullptr);
  ~LogManager();

  auto Write(const QString& message) -> void;

  private:
    QFile m_file;
    QTextStream m_stream;
};