#pragma once
#include <string>
#include <vector>

enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
};

class Logger {

public:
    Logger();
    void SetFile(const std::string &fileName);
    void SetMinLevel(LogLevel level);
    void Clear() const;
    void Write(LogLevel level, const std::string& text) const;
    void Write(LogLevel level, const char *fmt, ...) const;

private:
    std::string file = "";
    std::string levelText(LogLevel level) const;
    LogLevel minLevel = LogLevel::INFO;
    const std::vector<std::string> levelStrings{
        " DEBUG ",
        " INFO  ",
        "WARNING",
        " ERROR ",
        " FATAL ",
    };
};

extern Logger logger;
