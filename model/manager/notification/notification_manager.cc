#include "notification_manager.h"

NotificationManager::NotificationManager(QObject *parent) : QObject(parent) {
  loadSettings();
}

NotificationManager::~NotificationManager() { saveSettings(); }

auto NotificationManager::sendTellegramNotification(const QString &msg)
    -> bool {
  bool success{true};
  QString url = "https://api.telegram.org/bot" + m_token + "/sendMessage";
  QString post_data = "chat_id=" + m_chat + "&text=" + msg;

  CURL *curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.toLocal8Bit().constData());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
                     post_data.toLocal8Bit().constData());

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      success = false;
    }

    curl_easy_cleanup(curl);
  }
  return success;
}

auto NotificationManager::sendEmailNotification(const QString &msg) -> bool {
  CURL *curl = curl_easy_init();
  if (!curl) {
    return false;
  }

  // Установите URL-адрес SMTP-сервера и порт
  curl_easy_setopt(curl, CURLOPT_URL, m_url.toLocal8Bit().constData());
  curl_easy_setopt(curl, CURLOPT_PORT, m_port);

  // Установите имя пользователя и пароль для авторизации на SMTP-сервере
  curl_easy_setopt(curl, CURLOPT_USERNAME,
                   m_username.toLocal8Bit().constData());
  curl_easy_setopt(curl, CURLOPT_PASSWORD,
                   m_password.toLocal8Bit().constData());

  // Установите адрес отправителя
  curl_easy_setopt(curl, CURLOPT_MAIL_FROM, m_from.toLocal8Bit().constData());

  // Добавьте адрес получателя
  struct curl_slist *recipients =
      curl_slist_append(nullptr, m_to.toLocal8Bit().constData());
  curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

  // Формирование заголовка и тела письма
  m_header = "To: " + m_to + "\r\n";
  m_header += "From: " + m_from + "\r\n";
  m_header += "Subject: " + m_subject + "\r\n";
  m_header += "\r\n" + msg + "\r\n\r\n";

  // Установка параметров отправки
  struct ReadData rd = {0};
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, read);
  curl_easy_setopt(curl, CURLOPT_READDATA, &rd);
  curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }

  curl_slist_free_all(recipients);
  curl_easy_cleanup(curl);

  return res == CURLE_OK;
}

void NotificationManager::notification(const QString &message) {
  if (m_telegram) {
    sendTellegramNotification(message);
  }
  if (m_mail) {
    sendEmailNotification(message);
  }
}

size_t NotificationManager::read(char *ptr, size_t size, size_t nmemb,
                                 void *userp) {
  struct ReadData *rd = (struct ReadData *)userp;

  if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1)) {
    return 0;
  }

  const char *data = &m_header.toLocal8Bit().constData()[rd->bytes];
  if (data) {
    size_t room = size * nmemb;
    size_t lenth = strlen(data);
    if (room < lenth) {
      lenth = room;
    }
    memcpy(ptr, data, lenth);
    rd->bytes += lenth;

    return lenth;
  }

  return 0;
}

void NotificationManager::saveSettings() {
  m_setting.setValue("telegram", m_telegram);
  m_setting.setValue("token", m_token);
  m_setting.setValue("chat", m_chat);

  m_setting.setValue("mail", m_mail);
  m_setting.setValue("url", m_url);
  m_setting.setValue("username", m_username);
  m_setting.setValue("password", m_password);
  m_setting.setValue("from", m_from);
  m_setting.setValue("to", m_to);
  m_setting.setValue("subject", m_subject);
  m_setting.setValue("port", m_port);
}

void NotificationManager::loadSettings() {
  m_telegram = m_setting.value("telegram").toBool();
  m_token = m_setting.value("token").toString();
  m_chat = m_setting.value("chat").toString();

  m_mail = m_setting.value("mail").toBool();
  m_url = m_setting.value("url").toString();
  m_username = m_setting.value("username").toString();
  m_password = m_setting.value("password").toString();
  m_from = m_setting.value("from").toString();
  m_to = m_setting.value("to").toString();
  m_subject = m_setting.value("subject").toString();
  m_port = m_setting.value("port").toInt();
}
