#pragma once

#include <QAbstractListModel>
#include <QtCore>

#include "agent.h"

class AgentManager : public QAbstractListModel {
  Q_OBJECT

 public:
  enum Roles {
    kNameRole = Qt::UserRole + 1,
    kTypeRole
  };

  explicit AgentManager(QObject *parent = nullptr);

  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  virtual QHash<int, QByteArray> roleNames() const override;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
  virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

 private:
  QVector<Agent> m_data;
};
