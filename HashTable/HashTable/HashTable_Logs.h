#ifndef HASH_TABLE_LOGS_H
#define HASH_TABLE_LOGS_H

#include "..\Logs\Logs.h"

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

/// Конструкторы / деструкторы. 
#define LOG_CFG_HASH_TABLE_TRACE_CTOR true

/// Основные функции работы модуля.
/// Обычно располагаются в <ModuleName>.cpp.
#define LOG_CFG_HASH_TABLE_TRACE_FUNC_0 true

/// Второстепенные функции модуля.
/// Располагаются в вспомогательных файлах модуля.
#define LOG_CFG_HASH_TABLE_TRACE_FUNC_1 true

/// Вспомогательные функции модуля.
/// Часто вызываются, поэтому могут замусорить файл логов.
#define LOG_CFG_HASH_TABLE_TRACE_FUNC_2 true

/// Верификаторы, дампы.
//#define LOG_CFG_HASH_TABLE_TRACE_VERIFY true

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#if LOG_CFG_GLOBAL_TRACE_CTOR && LOG_CFG_HASH_TABLE_TRACE_CTOR
    #define LOG_HASH_TABLE_TRACE_CTOR LogTrace(LOG_SIG_HASH_TABLE)
#else 
    #define LOG_HASH_TABLE_TRACE_CTOR ((void)0)
#endif // !Ctor

#if LOG_CFG_GLOBAL_TRACE_FUNC_0 && LOG_CFG_HASH_TABLE_TRACE_FUNC_0
    #define LOG_HASH_TABLE_TRACE_FUNC_0 LogTrace(LOG_SIG_HASH_TABLE)
#else 
    #define LOG_HASH_TABLE_TRACE_FUNC_0 ((void)0)
#endif // !Func_0

#if LOG_CFG_GLOBAL_TRACE_FUNC_1 && LOG_CFG_HASH_TABLE_TRACE_FUNC_1
    #define LOG_HASH_TABLE_TRACE_FUNC_1 LogTrace(LOG_SIG_HASH_TABLE)
#else 
    #define LOG_HASH_TABLE_TRACE_FUNC_1 ((void)0)
#endif // !Func_1

#if LOG_CFG_GLOBAL_TRACE_FUNC_2 && LOG_CFG_HASH_TABLE_TRACE_FUNC_2
    #define LOG_HASH_TABLE_TRACE_FUNC_2 LogTrace(LOG_SIG_HASH_TABLE)
#else 
    #define LOG_HASH_TABLE_TRACE_FUNC_2 ((void)0)
#endif // !Func_2

#if LOG_CFG_GLOBAL_TRACE_VERIFY && LOG_CFG_HASH_TABLE_TRACE_VERIFY
    #define LOG_HASH_TABLE_TRACE_VERIFY LogTrace(LOG_SIG_HASH_TABLE)
#else 
    #define LOG_HASH_TABLE_TRACE_VERIFY ((void)0)
#endif // !Verify

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#define LOG_F_HASH_TABLE_ERR(format, ...) \
    LogFLine(LOG_LVL_ERROR, LOG_SIG_HASH_TABLE, LOG_GLOBAL_DUBLICATE_TO_CONSOLE, format, __VA_ARGS__)

#define LOG_HASH_TABLE_ERR(message) \
    LogLine(message, LOG_LVL_ERROR, LOG_SIG_HASH_TABLE, LOG_GLOBAL_DUBLICATE_TO_CONSOLE)

#define LOG_HASH_TABLE_ERR_MEMORY \
    LOG_HASH_TABLE_ERR("Ошибка выделения памяти")

#define LOG_HASH_TABLE_DBG(message) \
    LogLine(message, LOG_LVL_DEBUG, LOG_SIG_HASH_TABLE, true)

///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\
///***///***///---\\\***\\\***\\\___///***___***\\\___///***///***///---\\\***\\\***\\\

#endif // !HASH_TABLE_LOGS_H