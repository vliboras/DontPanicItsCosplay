// logger.c
#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// Текущий уровень логирования (можно менять во время выполнения)
static LogLevel current_log_level = LOG_INFO;

// Текстовые представления уровней логирования (используем enum для индексации)
static const char* const level_strings[LOG_LEVEL_COUNT] = {
    [LOG_TRACE]    = "TRACE",
    [LOG_DEBUG]    = "DEBUG",
    [LOG_INFO]     = "INFO",
    [LOG_WARNING]  = "WARNING",
    [LOG_ERROR]    = "ERROR",
    [LOG_CRITICAL] = "CRITICAL"
};

// Цвета для терминалов (опционально, также используем enum)
static const char* const level_colors[LOG_LEVEL_COUNT] = {
    [LOG_TRACE]    = "\x1B[36m",  // Cyan
    [LOG_DEBUG]    = "\x1B[32m",  // Green
    [LOG_INFO]     = "\x1B[37m",  // White
    [LOG_WARNING]  = "\x1B[33m",  // Yellow
    [LOG_ERROR]    = "\x1B[31m",  // Red
    [LOG_CRITICAL] = "\x1B[35m"   // Magenta
};

void logger_init(void) {
    // Проверка, что все уровни логирования инициализированы
    static_assert(
        sizeof(level_strings)/sizeof(level_strings[0]) == LOG_LEVEL_COUNT,
        "level_strings size mismatch"
    );
    static_assert(
        sizeof(level_colors)/sizeof(level_colors[0]) == LOG_LEVEL_COUNT,
        "level_colors size mismatch"
    );

    // Здесь можно инициализировать аппаратные средства,
    // необходимые для логирования (например, UART)
}

void log_message(LogLevel level, const char* format, ...) {
    if (level < current_log_level) return;

    // Буфер для сообщения (можно сделать динамическим или увеличить размер)
    char buf[256];
    va_list args;
    va_start(args, format);

    // Добавляем метку времени (если есть RTC или системный тикер)
    // uint32_t timestamp = get_system_tick(); // Пример для вашей системы
    // snprintf(buf, sizeof(buf), "[%lu] ", timestamp);

    // Добавляем уровень логирования (с проверкой выхода за границы)
    const char* level_str = (level < LOG_LEVEL_COUNT) ? 
                            level_strings[level] : "UNKNOWN";
    int len = snprintf(buf, sizeof(buf), "[%s] ", level_str);
    
    // Форматируем основное сообщение
    if (len > 0 && len < (int)sizeof(buf)) {
        vsnprintf(buf + len, sizeof(buf) - len, format, args);
    }

    // Добавляем перевод строки, если его нет
    len = strlen(buf);
    if (len > 0 && buf[len-1] != '\n' && len < (int)sizeof(buf) - 1) {
        strncat(buf, "\n", sizeof(buf) - len - 1);
    }

    // Выводим через printf (который у вас работает через UART)
    printf("%s", buf);

    va_end(args);
}