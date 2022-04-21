#ifndef __HDR_SHARED_LOGGER__
#define __HDR_SHARED_LOGGER__
#endif

#include "SharedLibInit.h"
#include "Singleton.h"

#include <formatter/format.h>
#include <string>
#include <time.h>
#include <Windows.h>

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif // USING_QTLIB

#define LOGD(LOGTYPE, ...) \
    TyStLog::GetInstance()->Debug(LOGTYPE, __FILE__, __LINE__, fmt::format(__VA_ARGS__))

#define CONSOLEP(...) \
    TyStLog::GetInstance()->ConsolePrint( __FILE__, __LINE__, fmt::format(__VA_ARGS__))

#define USE_LOGGER_INIT

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
            static void              Debug( std::string LOGTYPE, const char* fileName, int codeLine, std::string format );
            static void              Debug( std::string LOGTYPE, const char* fileName, int codeLine, std::wstring format );

            static void              ConsolePrint( const char* fileName, int codeLine, std::wstring format );
            // 파일 기록용 로그
            static void              Recode( const char* LOGTYPE, const char* fileName, int codeLine, std::string format );

        private:
            inline static bool       _isFileLogging;
        };
    }
}

typedef Shared::Singletons::Singleton<Shared::Logger::Log> TyStLog;