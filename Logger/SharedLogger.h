#ifndef __HDR_SHARED_LOGGER__
#define __HDR_SHARED_LOGGER__
#endif

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

#define USE_LOGGER_INIT

namespace Shared
{
    namespace Logger
    {
        class Log
        {
        public:
            Log() {}
            ~Log() {}

            // ����׿� �α�
            static void Debug( std::string LOGTYPE, const char* fileName, int codeLine, std::string format );

            // ���� ��Ͽ� �α�
            static void Recode( const char* LOGTYPE, const char* fileName, int codeLine, std::string format );
        };
    }
}

typedef Shared::Singletons::Singleton<Shared::Logger::Log> TyStLog;