#ifndef __HDR_INCLUDE_SHARED__
#define __HDR_INCLUDE_SHARED__

#include "config.h"

#ifdef USING_SHARED_LOGGER
    #include "SharedLogger.h"
    #define NAMESPACE_SHARED_LOGGER using namespace Shared::Logger;

#define LOGD(...) \
    TyStLog::GetInstance()->LogCase(TyEnLogger::LOGGER_DEBUG, __FILE__, __LINE__, std::format(__VA_ARGS__))

#define CONSOLEP(...) \
    TyStLog::GetInstance()->LogCase(TyEnLogger::LOGGER_CONSOLE, __FILE__, __LINE__, std::format(__VA_ARGS__))

#else

#define LOGD(...)
#define CONSOLEP(...)
    
#endif

#ifdef USING_LOGGER_LIB
#define LOGLIB(LOGTYPE, ...) \
    TyStLog::GetInstance()->LogCase(TyEnLogger::LOGGER_LIBS, __FILE__, __LINE__, std::format(__VA_ARGS__))
#else
#define LOGLIB( LOGTYPE, ... )
#endif


#ifndef SET_CONFIG
    static_assert( false, "Modify the 'config.h.sample' file and save it as a 'config.h'" );
#endif // ! SET_CONFIG

#endif