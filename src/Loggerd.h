#ifndef LOGGERD_H
#define LOGGERD_H

#include <list>
#include <memory>
#include <string>

#include "config.h"
#include "MessageHandler.h"

class Loggerd {
public:
    enum class LogLevel {
        Debug,
        Info,
        Critical,
        Trace
    };

    static Loggerd* getInstance();
    void addMessageHandler(MessageHandler* messageHandler);
    void log(LogLevel level, const std::string& message, const char* file = nullptr, int line = -1);
    void logDebug(const std::string& message, const char* file = nullptr, int line = -1);
    void logInfo(const std::string& message, const char* file = nullptr, int line = -1);
    void logCritical(const std::string& message, const char* file = nullptr, int line = -1);
    void logTrace(const std::string& message, const char* file = nullptr, int line = -1);
    ~Loggerd();

private:
    Loggerd();
    static const char* toString(LogLevel level);
    static std::string formatMessage(LogLevel level, const std::string& message, const char* file, int line);

    static std::unique_ptr<Loggerd> m_instance;
    std::list<MessageHandler*> m_messageHandlers;
};

#if LOG_DEBUG
#define LOG_DEBUG_MSG(message) Loggerd::getInstance()->logDebug((message), __FILE__, __LINE__)
#else
#define LOG_DEBUG_MSG(message) do { } while (false)
#endif

#if LOG_INFO
#define LOG_INFO_MSG(message) Loggerd::getInstance()->logInfo((message), __FILE__, __LINE__)
#else
#define LOG_INFO_MSG(message) do { } while (false)
#endif

#if LOG_CRITICAL
#define LOG_CRITICAL_MSG(message) Loggerd::getInstance()->logCritical((message), __FILE__, __LINE__)
#else
#define LOG_CRITICAL_MSG(message) do { } while (false)
#endif

#if LOG_TRACE
#define LOG_TRACE_MSG(message) Loggerd::getInstance()->logTrace((message), __FILE__, __LINE__)
#else
#define LOG_TRACE_MSG(message) do { } while (false)
#endif

#endif // LOGGERD_H
