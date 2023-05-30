#include "notification_manager.h"

NotificationManager::NotificationManager(QObject *parent) : QObject(parent) {}

NotificationManager::~NotificationManager() {}

auto NotificationManager::sendTellegramNotification(const std::string msg)
    -> bool {
  bool success{true};
  std::string url = "https://api.telegram.org/bot" + m_token + "/sendMessage";
  std::string post_data = "chat_id=" + m_chat + "&text=" + msg;

  CURL *curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      success = false;
    }

    curl_easy_cleanup(curl);
  }
  return success;
}

auto NotificationManager::sendEmailNotification(const std::string msg) -> bool {
  CURL *curl = curl_easy_init();
  if (curl) {
    // Установка параметров SMTP-сервера
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.example.com");
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "sender@example.com");
    struct curl_slist *recipients = NULL;
    recipients = curl_slist_append(recipients, "recipient@example.com");
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    // Установка тела письма
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_READDATA, NULL);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    const char *payload_text = msg.c_str();
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)strlen(payload_text));
    // curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, payload_text);

    // Отправка письма
    CURLcode res = curl_easy_perform(curl);

    // Проверка результата отправки
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    // Освобождение ресурсов
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
  }
}
