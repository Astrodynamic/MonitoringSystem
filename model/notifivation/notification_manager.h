#pragma once

class NotificationManager {
 public:
  void sendTelegramNotification(const std::string& message) {
    // Отправка уведомления в Telegram
  }

  void sendEmailNotification(const std::string& recipient,
                             const std::string& subject,
                             const std::string& message) {
    // Отправка уведомления на электронную почту
  }
};
