#include "Loggerd.h"
#include <ctime>
#include <iomanip>
#include <sstream>

namespace {
const char* getFileName(const char* path) {
    if (path == nullptr) {
        return nullptr;
    }

    const char* lastSlash = path;
    for (const char* current = path; *current != '\0'; ++current) {
        if (*current == '/' || *current == '\\') {
            lastSlash = current + 1;
        }
    }

    return lastSlash;
}
}  // namespace

std::unique_ptr<Loggerd> Loggerd::m_instance = nullptr;

Loggerd::Loggerd() {

}

Loggerd *Loggerd::getInstance()
{
    if (!m_instance) {
        m_instance.reset(new Loggerd());
    }

    return m_instance.get();
}

void Loggerd::addMessageHandler(MessageHandler *messageHandler)
{
    if (messageHandler) {
        m_messageHandlers.push_back(messageHandler);
    }
}

void Loggerd::log(LogLevel level, const std::string& message, const char* file, int line) {
    const std::string formattedMessage = formatMessage(level, message, file, line);

    for (MessageHandler* messageHandler : m_messageHandlers) {
        if (messageHandler) {
            messageHandler->sendMessage(formattedMessage);
        }
    }
}

void Loggerd::logDebug(const std::string& message, const char* file, int line) {
    log(LogLevel::Debug, message, file, line);
}

void Loggerd::logInfo(const std::string& message, const char* file, int line) {
    log(LogLevel::Info, message, file, line);
}

void Loggerd::logCritical(const std::string& message, const char* file, int line) {
    log(LogLevel::Critical, message, file, line);
}

void Loggerd::logTrace(const std::string& message, const char* file, int line) {
    log(LogLevel::Trace, message, file, line);
}

const char* Loggerd::toString(LogLevel level) {
    switch (level) {
        case LogLevel::Debug:
            return "DEBUG";
        case LogLevel::Info:
            return "INFO";
        case LogLevel::Critical:
            return "CRITICAL";
        case LogLevel::Trace:
            return "TRACE";
        default:
            return "UNKNOWN";
    }
}

std::string Loggerd::formatMessage(LogLevel level, const std::string& message, const char* file, int line) {
    std::time_t now = std::time(nullptr);
    std::tm tm {};
    localtime_r(&now, &tm);

    std::ostringstream timestamp;
    timestamp << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    std::string formatted = "[" + std::string(toString(level)) + "] "
        + "[" + timestamp.str() + "] ";

    if (file != nullptr && line >= 0) {
        formatted += "[" + std::string(getFileName(file)) + ":" + std::to_string(line) + "] ";
    } else if (line >= 0) {
        formatted += "[line:" + std::to_string(line) + "] ";
    }

    formatted += message;
    return formatted;
}

Loggerd::~Loggerd() {

}
