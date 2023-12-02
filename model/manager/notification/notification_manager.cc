#include "notification_manager.h"

#define FROM_MAIL     "<s21monitoring@rambler.ru>"
#define TO_MAIL       "<Astrodynamic.fkg@yandex.ru>"

static const char *payload_text =
    "To: " TO_MAIL "\r\n"
    "From: " FROM_MAIL "\r\n"
    "Subject: SMTP example message\r\n"
    "\r\n" /* empty line to divide headers from body, see RFC 5322 */
    "The body of the message starts here.\r\n"
    "\r\n"
    "It could be a lot of lines, could be MIME encoded, whatever.\r\n"
    "YA PIDARASKA\r\n";

struct upload_status {
    size_t bytes_read;
};

static size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp) {
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;
    size_t room = size * nmemb;

    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    data = &payload_text[upload_ctx->bytes_read];

    if(data) {
        size_t len = strlen(data);
        if(room < len)
            len = room;
        memcpy(ptr, data, len);
        upload_ctx->bytes_read += len;

        return len;
    }

    return 0;
}

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

auto NotificationManager::sendEmailNotification(const QString &msg) -> bool {
  CURL* curl = curl_easy_init();
  if (!curl) {
    return false;
  }

  // Установите имя пользователя и пароль для авторизации на SMTP-сервере
  curl_easy_setopt(curl, CURLOPT_USERNAME, "s21monitoring@rambler.ru");
  curl_easy_setopt(curl, CURLOPT_PASSWORD, "S21monitoring");

  // Установите URL-адрес SMTP-сервера и порт
  curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.rambler.ru:587");

  // Установите адрес отправителя
  curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<s21monitoring@rambler.ru>");

  // Добавьте адрес получателя
  struct curl_slist* recipients = curl_slist_append(nullptr, "<Astrodynamic.fkg@yandex.ru>");
  curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

  // Формирование заголовка письма
  std::string header;
  header += "To: <Astrodynamic.fkg@yandex.ru>\r\n";
  header += "From: <s21monitoring@rambler.ru>\r\n";
  header += "Subject: MonitoringSystem WARNIG\r\n";

  // Формирование тела письма
  std::string email = header + "\r\n" + "WARNING";

  // Установка параметров отправки
  struct upload_status upload_ctx = { 0 };
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
  curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
  curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
  }

  curl_slist_free_all(recipients);
  curl_easy_cleanup(curl);

  return res == CURLE_OK;
}

void NotificationManager::notification(const QString &message) {
    sendEmailNotification(message);
}
