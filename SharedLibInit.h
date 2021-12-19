#ifndef __HDR_INCLUDE_SHARED__
#define __HDR_INCLUDE_SHARED__

#ifdef USING_SHARED_LOGGER
    #include "SharedLogger.h"
    #define NAMESPACE_SHARED_LOGGER using namespace Shared::Logger;
#endif