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

Loggerd::Loggerd() {

}

Loggerd *Loggerd::getInstance()
{
    static Loggerd instance;
    return &instance;
}

void Loggerd::addMessageHandler(MessageHandler *messageHandler)
{
    if (!messageHandler) {
        return;
    }
    std::lock_guard<std::mutex> lock(m_handlersMutex);
    m_messageHandlers.push_back(messageHandler);
}

void Loggerd::log(LogLevel level, const std::string& message, const char* file, int line) {
    const std::string formattedMessage = formatMessage(level, message, file, line);

    std::list<MessageHandler*> handlersSnapshot;
    {
        std::lock_guard<std::mutex> lock(m_handlersMutex);
        handlersSnapshot = m_messageHandlers;
    }

    for (MessageHandler* messageHandler : handlersSnapshot) {
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
