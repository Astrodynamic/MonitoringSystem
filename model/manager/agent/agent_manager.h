#pragma once

#include <QAbstractListModel>
#include <QtCore>
#include <QObject>

#include "agent.h"

class AgentManager : public QAbstractListModel {
  Q_OBJECT

 public:
  enum Roles {
    kNameRole = Qt::UserRole + 1,
    kTypeRole
  };

  explicit AgentManager(QObject *parent = nullptr);

  virtual auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int override;
  virtual auto data(const QModelIndex &index, int role = Qt::DisplayRole) const -> QVariant override;
  virtual auto roleNames() const -> QHash<int, QByteArray> override;
  virtual auto setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) -> bool override;
  virtual auto flags(const QModelIndex &index) const -> Qt::ItemFlags override;
  virtual auto removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) -> bool override;

  auto registerAgent(const QString &path, AgentSettings & settings) -> bool;

 private:
  QVector<Agent *> m_data;
};
