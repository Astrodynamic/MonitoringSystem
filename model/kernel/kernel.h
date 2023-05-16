#pragma once

#include <QAbstractListModel>

#include "agent.h"

class Kernel : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit Kernel(QObject *parent = nullptr);

  private:
    
};
