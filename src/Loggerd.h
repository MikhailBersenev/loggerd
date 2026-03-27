#ifndef LOGGERD_H
#define LOGGERD_H

#include <list>
#include <mutex>
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
    void logNothing() { };
    ~Loggerd();

private:
    Loggerd();
    static const char* toString(LogLevel level);
    static std::string formatMessage(LogLevel level, const std::string& message, const char* file, int line);

    std::mutex m_handlersMutex;
    std::list<MessageHandler*> m_messageHandlers;
};

#if LOG_LEVEL >= LOG_DEBUG
#define LOG_DEBUG_MSG(level, message) Loggerd::getInstance()->logDebug((message), __FILE__, __LINE__)
#else
#define LOG_DEBUG_MSG(level, message) level >= LOG_DEBUG ? Loggerd::getInstance()->logDebug((message), __FILE__, __LINE__) : Loggerd::getInstance()->logNothing()
#endif

#if LOG_LEVEL >= LOG_INFO
#define LOG_INFO_MSG(level, message) Loggerd::getInstance()->logInfo((message), __FILE__, __LINE__)
#else
#define LOG_INFO_MSG(level, message) level >= LOG_INFO ? Loggerd::getInstance()->logInfo((message), __FILE__, __LINE__) : Loggerd::getInstance()->logNothing()
#endif

#if LOG_LEVEL >= LOG_CRITICAL
#define LOG_CRITICAL_MSG(level, message) Loggerd::getInstance()->logCritical((message), __FILE__, __LINE__)
#else
#define LOG_CRITICAL_MSG(level, message) level >= LOG_CRITICAL ? Loggerd::getInstance()->logCritical((message), __FILE__, __LINE__) : Loggerd::getInstance()->logNothing()
#endif

#if LOG_LEVEL >= LOG_TRACE
#define LOG_TRACE_MSG(level, message)  Loggerd::getInstance()->logTrace((message), __FILE__, __LINE__)
#else
#define LOG_TRACE_MSG(level, message) level >= LOG_TRACE ? Loggerd::getInstance()->logTrace((message), __FILE__, __LINE__) : Loggerd::getInstance()->logNothing()
#endif

#endif // LOGGERD_H
