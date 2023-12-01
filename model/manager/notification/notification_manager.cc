#include "notification_manager.h"

NotificationManager::NotificationManager(QObject *parent) : QObject(parent) {}

NotificationManager::~NotificationManager() {}

auto NotificationManager::sendTellegramNotification(const QString &msg) -> bool {
  bool success{true};
  QString url = "https://api.telegram.org/bot" + m_token + "/sendMessage";
  QString post_data = "chat_id=" + m_chat + "&text=" + msg;

  CURL *curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.toLocal8Bit().constData());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.toLocal8Bit().constData());

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      success = false;
    }

    curl_easy_cleanup(curl);
  }
  return success;
}

auto NotificationManager::sendEmailNotification(const std::string& subject, const std::string& msg) -> bool {
  CURL* curl = curl_easy_init();
  if (!curl) {
    return false;
  }

  // Установите URL-адрес SMTP-сервера и порт
  curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.example.com:587");

  // Установите имя пользователя и пароль для авторизации на SMTP-сервере
  curl_easy_setopt(curl, CURLOPT_USERNAME, "username");
  curl_easy_setopt(curl, CURLOPT_PASSWORD, "password");

  // Установите адрес отправителя
  curl_easy_setopt(curl, CURLOPT_MAIL_FROM, m_from.c_str());

  // Добавьте адрес получателя
  struct curl_slist* recipients = curl_slist_append(nullptr, m_to.c_str());
  curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

  // Формирование заголовка письма
  std::string header = "Subject: " + subject + "\r\n";
  header += "To: " + m_to + "\r\n";
  header += "From: " + m_from + "\r\n";

  // Формирование тела письма
  std::string email = header + "\r\n" + msg;

  // Установка параметров отправки
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, nullptr);
  curl_easy_setopt(curl, CURLOPT_READDATA, email.c_str());
  curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
  curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, static_cast<curl_off_t>(email.length()));

  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
  }

  curl_slist_free_all(recipients);
  curl_easy_cleanup(curl);

  return res == CURLE_OK;
}

void NotificationManager::notification(const QString &message) {
    sendTellegramNotification(message);
}
