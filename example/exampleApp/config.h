#ifndef CONFIG_H
#define CONFIG_H

// Application-owned loggerd configuration.
// Copy/adjust values as needed for your build.

#ifndef LOG_DEBUG
#define LOG_DEBUG 2
#endif

#ifndef LOG_INFO
#define LOG_INFO 3
#endif

#ifndef LOG_CRITICAL
#define LOG_CRITICAL 1
#endif

#ifndef LOG_TRACE
#define LOG_TRACE 4
#endif

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_TRACE
#endif

#ifndef LOG_MAIN
#define LOG_MAIN LOG_CRITICAL
#endif

#endif

