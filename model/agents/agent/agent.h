#pragma once

class Agent {
public:
    virtual void collectMetrics() = 0;
};

class CpuLoadAgent : public Agent {
public:
    void collectMetrics() override {
        // Сбор метрик CPU
    }
};

class MemoryAgent : public Agent {
public:
    void collectMetrics() override {
        // Сбор метрик памяти
    }
};

class NetworkAgent : public Agent {
public:
    void collectMetrics() override {
        // Сбор метрик сети
    }
};

class LogManager {
public:
    void createLogFile(const std::string& fileName) {
        // Создание нового лог-файла с заданным именем
    }

    void writeMetricsToLog(const std::string& metrics) {
        // Запись метрик в лог-файл
    }

    std::vector<std::string> getLastLogLines(int lineCount) {
        // Получение последних N строк из лог-файла
    }
};

class ConfigurationManager {
public:
    void loadAgentConfiguration(const std::string& agentName) {
        // Загрузка конфигурационного файла агента по его имени
    }

    void saveAgentConfiguration(const std::string& agentName) {
        // Сохранение конфигурационного файла агента
    }

    void updateAgentConfiguration(const std::string& agentName, const std::string& configuration) {
        // Обновление конфигурации агента
    }
};

class NotificationManager {
public:
    void sendTelegramNotification(const std::string& message) {
        // Отправка уведомления в Telegram
    }

    void sendEmailNotification(const std::string& recipient, const std::string& subject, const std::string& message) {
        // Отправка уведомления на электронную почту
    }
};
