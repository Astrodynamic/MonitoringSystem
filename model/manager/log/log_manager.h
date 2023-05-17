#pragma once

class LogManager {
 public:
  void createLogFile(const std::string& fileName);
  void writeMetricsToLog(const std::string& metrics);
  std::vector<std::string> getLastLogLines(int lineCount);
};