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

auto NotificationManager::sendEmailNotification(const std::string message) -> bool {
  CURL* curl = curl_easy_init();
  if (!curl) {
    return false;
  }

  curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.example.com");
  curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "sender@example.com");
  struct curl_slist* recipients = curl_slist_append(nullptr, "recipient@example.com");
  curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

  curl_easy_setopt(curl, CURLOPT_READFUNCTION, nullptr);
  curl_easy_setopt(curl, CURLOPT_READDATA, message.c_str());
  curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
  curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, static_cast<curl_off_t>(message.length()));

  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
  }

  curl_slist_free_all(recipients);
  curl_easy_cleanup(curl);

  return res == CURLE_OK;
}
