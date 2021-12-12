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
            // ����׿� �α�
            static void Debug( const char* LOGTYPE, const char* fileName, int codeLine, std::string format );

            // ���� ��Ͽ� �α�
            static void Recode( const char* LOGTYPE, const char* fileName, int codeLine, std::string format );
        private:
            Log() {}
            virtual ~Log() {}
        };
    }
}
