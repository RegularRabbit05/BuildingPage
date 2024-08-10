#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <cstdlib>

void TraceLogFunction(int logType, const char *text, va_list args)
{
    if (strcmp(text, "MODEL: UpdateModelAnimation(): Mesh %i has no connection to bones") == 0) {
        return;
    }

    const int MAX_TRACELOG_MSG_LENGTH = 256;

    enum Levels {
        LOG_ALL = 0,        // Display all logs
        LOG_TRACE,          // Trace logging, intended for internal use only
        LOG_DEBUG,          // Debug logging, used for internal debugging, it should be disabled on release builds
        LOG_INFO,           // Info logging, used for program execution info
        LOG_WARNING,        // Warning logging, used on recoverable failures
        LOG_ERROR,          // Error logging, used on unrecoverable failures
        LOG_FATAL,          // Fatal logging, used to abort program: exit(EXIT_FAILURE)
        LOG_NONE            // Disable logging
    };

    char buffer[MAX_TRACELOG_MSG_LENGTH] = { 0 };

    if (logType == LOG_NONE) return;

    switch (logType)
    {
        case LOG_TRACE: strcpy(buffer, "TRACE: "); break;
        case LOG_DEBUG: strcpy(buffer, "DEBUG: "); break;
        case LOG_INFO: strcpy(buffer, "INFO: "); break;
        case LOG_WARNING: strcpy(buffer, "WARNING: "); break;
        case LOG_ERROR: strcpy(buffer, "ERROR: "); break;
        case LOG_FATAL: strcpy(buffer, "FATAL: "); break;
        default: break;
    }

    unsigned int textSize = (unsigned int)strlen(text);
    memcpy(buffer + strlen(buffer), text, (textSize < (MAX_TRACELOG_MSG_LENGTH - 12))? textSize : (MAX_TRACELOG_MSG_LENGTH - 12));
    strcat(buffer, "\n");
    vprintf(buffer, args);
    fflush(stdout);

    if (logType == LOG_FATAL) exit(EXIT_FAILURE);
}