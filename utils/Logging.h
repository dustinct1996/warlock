#ifndef LOGGING_H
#define LOGGING_H

#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <filesystem>

enum class Severity {
    INFO,
    WARNING,
    ERROR
};

inline const char* toString(Severity s) {
    switch (s) {
        case Severity::INFO:    return "INFO";
        case Severity::WARNING: return "WARNING";
        case Severity::ERROR:   return "ERROR";
        default:                return "UNKNOWN";
    }
}

class LogMessage {
public:
    LogMessage(Severity logSeverity, const char* sourceFile, int logLine) {
        severity = logSeverity;
        file = sourceFile;
        line = logLine;
    }

    ~LogMessage() {
        std::cout << "[" << toString(severity) << "] "
                  << std::filesystem::path(file).filename().string().c_str() << ":" << line
                  << " (" << currentTimestamp() << "): "
                  << stream.str()
                  << std::endl;
    }

    template<typename T>
    LogMessage& operator<<(const T& value) {
        stream << value;
        return *this;
    }

private:
    std::string currentTimestamp() const {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        std::tm time_buffer{};
#ifdef _WIN32
        localtime_s(&time_buffer, &now);
#else
        localtime_r(&now, &time_buffer);
#endif

        std::ostringstream ss;
        ss << std::put_time(&time_buffer, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    Severity severity;
    const char* file;
    int line;
    std::ostringstream stream;
};

class DummyStream {
public:
    template<typename T>
    DummyStream& operator<<(const T&) {
        return *this;
    }
};

#ifdef DEVELOPER_BUILD
#define LOG(level) LogMessage(Severity::level, __FILE__, __LINE__)
#else
#define LOG(level) DummyStream()
#endif

#endif // LOGGING_H