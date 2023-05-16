#pragma once

#include <QObject>

class Kernel : public QObject {
  Q_OBJECT
 public:
  explicit Kernel(QObject *parent = nullptr);

};
