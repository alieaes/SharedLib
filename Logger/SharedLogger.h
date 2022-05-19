#ifndef __HDR_SHARED_LOGGER__
#define __HDR_SHARED_LOGGER__
#endif

#pragma once

#include "SharedLibInit.h"
#include "Singleton.h"

#include <format>

#include <string>
#include <time.h>
#include <Windows.h>

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif // USING_QTLIB

#define USE_LOGGER_INIT

typedef enum
{
    LOGGER_NONE,
    LOGGER_DEBUG,
    LOGGER_CONSOLE,
    LOGGER_LIBS
} TyEnLogger;

namespace Shared
{
    namespace Logger
    {
        typedef struct _LOGGER
        {
            bool                     isFileLogging = false;
        } TyLogger;

        class Log
        {
        public:
            Log() {}
            ~Log() {}

            static void              init( TyLogger tyLogger );
            // 디버그용 로그
            static void              LogCase( TyEnLogger eLogType, const char* fileName, int codeLine, std::string format );
            static void              LogCase( TyEnLogger eLogType, const char* fileName, int codeLine, std::wstring format );

            static void              Logging( const char* fileName, int codeLine, std::string format );
            static void              Logging( const char* fileName, int codeLine, std::wstring format );

            static void              ConsolePrint( std::wstring format );
            static void              ConsolePrint( std::string format );

        private:
            inline static bool       _isFileLogging;
        };
    }
}

typedef Shared::Singletons::Singleton<Shared::Logger::Log> TyStLog;