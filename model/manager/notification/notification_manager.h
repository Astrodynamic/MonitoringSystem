#pragma once

#include <QObject>
#include <QDebug>
#include <curl/curl.h>
#include <string>

class NotificationManager : public QObject {
  Q_OBJECT

 public:
  explicit NotificationManager(QObject *parent = nullptr);
  virtual ~NotificationManager();

  auto sendTellegramNotification(const QString &msg) -> bool;
  auto sendEmailNotification(const std::string& subject, const std::string& msg) -> bool;

 public slots:
  auto notification(const QString& message) -> void;

 private:
  QString m_token;
  QString m_chat;
  std::string m_from;
  std::string m_to;
};
