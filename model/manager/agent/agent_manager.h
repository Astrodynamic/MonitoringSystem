#pragma once

#include <QAbstractListModel>
#include <QLibrary>
#include <QtCore>
#include <QObject>

#include "agent.h"
#include "log_manager.h"

class AgentManager : public QAbstractListModel {
  Q_OBJECT

 public:
  enum Roles {
    kEnabledRole = Qt::UserRole + 1,
    kNameRole,
    kTypeRole,
    kIntervalRole,
    kConfigRole,
    kTimerRole,
    kMetricsRole
  };

  explicit AgentManager(QObject *parent = nullptr);
  virtual ~AgentManager();

  virtual auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int override;
  virtual auto data(const QModelIndex &index, int role = Qt::DisplayRole) const -> QVariant override;
  virtual auto roleNames() const -> QHash<int, QByteArray> override;
  virtual auto setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) -> bool override;
  virtual auto flags(const QModelIndex &index) const -> Qt::ItemFlags override;
  virtual auto removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) -> bool override;

  auto registerAgent(const QString &path, AgentSettings & settings) -> bool;

 public slots:
  auto config(int index) -> QString;
  auto config(int index, QString json) -> void;

 signals:
  auto updateConfiguration(const QString & path, AgentSettings &settings) -> void;
  auto updateLogs(const QString& message, LogManager::LogLevel level = LogManager::LogLevel::kDEBUG) -> void;

 private:
  QVector<QPair<QSharedPointer<QLibrary>, QSharedPointer<Agent>>> m_data;
  QTimer m_timer;
};
