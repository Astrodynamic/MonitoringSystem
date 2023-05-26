#pragma once

#include <QObject>

class LogManager : public QObject {
  Q_OBJECT

 public:
  explicit LogManager(QObject *parent = nullptr);
  ~LogManager();


  private:

};