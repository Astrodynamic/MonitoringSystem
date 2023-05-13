#pragma once

#include <string>

class Kernel {
    void scanAgentsFolder();
    void collectMetrics();
    void logMetrics(const std::string& metrics);
};