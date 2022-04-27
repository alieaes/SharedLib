#ifndef __HDR_INCLUDE_SHARED__
#define __HDR_INCLUDE_SHARED__

#include "config.h"

#ifdef USING_SHARED_LOGGER
    #include "SharedLogger.h"
    #define NAMESPACE_SHARED_LOGGER using namespace Shared::Logger;
#endif

#ifndef SET_CONFIG
    static_assert( false, "Modify the 'config.h.sample' file and save it as a 'config.h'" );
#endif // ! SET_CONFIG

#endif