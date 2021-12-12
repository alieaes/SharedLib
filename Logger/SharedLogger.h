#ifndef __HDR_SHARED_LOGGER__
#define __HDR_SHARED_LOGGER__
#endif

#include <formatter/format.h>
#include <string>
#include <time.h>
#include <Windows.h>

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif // USING_QTLIB

#define LOGD(LOGTYPE, ...) \
    Library::Logger::Log *LbLogger; \
    LbLogger->Debug(LOGTYPE, __FILE__, __LINE__, fmt::format(__VA_ARGS__))
#define USE_LOGGER_INIT

namespace Library
{
    namespace Logger
    {
        class Log
        {
        public:
            // 디버그용 로그
            static void Debug( const char* LOGTYPE, const char* fileName, int codeLine, std::string format );

            // 파일 기록용 로그
            static void Recode( const char* LOGTYPE, const char* fileName, int codeLine, std::string format );
        private:
            Log() {}
            virtual ~Log() {}
        };
    }
}
