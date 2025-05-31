// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>

// Уровни логирования
typedef enum {
    LOG_TRACE = 0,    // Подробная отладочная информация
    LOG_DEBUG,        // Отладочные сообщения
    LOG_INFO,         // Информационные сообщения
    LOG_WARNING,      // Предупреждения
    LOG_ERROR,        // Ошибки
    LOG_CRITICAL,     // Критические ошибки
    LOG_LEVEL_COUNT   // Количество уровней (автоматически)
} LogLevel;

// Инициализация логгера (если нужно)
void logger_init(void);

// Основная функция логирования
void log_message(LogLevel level, const char* format, ...);

// Макросы для удобства
#if defined(ENABLE_LOGGING) || defined(DEBUG)
    #define LOG_TRACE(...)    log_message(LOG_TRACE, __VA_ARGS__)
    #define LOG_DEBUG(...)    log_message(LOG_DEBUG, __VA_ARGS__)
    #define LOG_INFO(...)     log_message(LOG_INFO, __VA_ARGS__)
    #define LOG_WARNING(...)  log_message(LOG_WARNING, __VA_ARGS__)
    #define LOG_ERROR(...)    log_message(LOG_ERROR, __VA_ARGS__)
    #define LOG_CRITICAL(...) log_message(LOG_CRITICAL, __VA_ARGS__)
#else
    // В релизе логи можно отключить
    #define LOG_TRACE(...)    
    #define LOG_DEBUG(...)    
    #define LOG_INFO(...)     
    #define LOG_WARNING(...)  
    #define LOG_ERROR(...)    
    #define LOG_CRITICAL(...)
#endif

#endif // LOGGER_H