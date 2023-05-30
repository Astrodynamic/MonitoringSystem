#include "notification_manager.h"

NotificationManager::NotificationManager(QObject* parent) : QObject(parent) {}

NotificationManager::~NotificationManager() {}

auto NotificationManager::sendTellegramNotification(const std::string msg) -> bool {
  bool success{true};
  std::string url = "https://api.telegram.org/bot" + m_token + "/sendMessage";
  std::string post_data = "chat_id=" + m_chat + "&text=" + msg;

  CURL* curl = curl_easy_init();
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
  
}