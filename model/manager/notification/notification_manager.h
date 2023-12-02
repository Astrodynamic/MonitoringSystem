#pragma once

#include <QObject>
#include <QSettings>
#include <curl/curl.h>

class NotificationManager : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString token MEMBER m_token NOTIFY tokenChanged)
  Q_PROPERTY(QString chat MEMBER m_chat NOTIFY chatChanged)
  Q_PROPERTY(QString url MEMBER m_url NOTIFY urlChanged)
  Q_PROPERTY(QString username MEMBER m_username NOTIFY usernameChanged)
  Q_PROPERTY(QString password MEMBER m_password NOTIFY passwordChanged)
  Q_PROPERTY(QString from MEMBER m_from NOTIFY fromChanged)
  Q_PROPERTY(QString to MEMBER m_to NOTIFY toChanged)
  Q_PROPERTY(QString subject MEMBER m_subject NOTIFY subjectChanged)
  Q_PROPERTY(int port MEMBER m_port NOTIFY portChanged)
  Q_PROPERTY(bool telegram MEMBER m_telegram NOTIFY telegramChanged)
  Q_PROPERTY(bool mail MEMBER m_mail NOTIFY mailChanged)

 public:
  explicit NotificationManager(QObject *parent = nullptr);
  virtual ~NotificationManager();

  auto sendTellegramNotification(const QString &msg) -> bool;
  auto sendEmailNotification(const QString &msg) -> bool;

 public slots:
  auto notification(const QString& message) -> void;

 signals:
  void tokenChanged();
  void chatChanged();
  void urlChanged();
  void usernameChanged();
  void passwordChanged();
  void fromChanged();
  void toChanged();
  void subjectChanged();
  void portChanged();
  void telegramChanged();
  void mailChanged();

  private:
  struct ReadData {
    size_t bytes;
  };

  static inline QString m_header;

  bool m_telegram;
  QString m_token;
  QString m_chat;

  bool m_mail;
  QString m_url;
  QString m_username;
  QString m_password;
  QString m_from;
  QString m_to;
  QString m_subject;
  int m_port;

  QSettings m_setting;

 private:
  static size_t read(char *ptr, size_t size, size_t nmemb, void *userp);

  void saveSettings();
  void loadSettings();
};
