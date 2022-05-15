#ifndef __HDR_SHARED_CURL__
#define __HDR_SHARED_CURL__
#endif

#include <string>
#include <Windows.h>

#include "config.h"

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif // USING_QTLIB

#ifdef USING_CURL

namespace Shared
{
    namespace Curl
    {
        bool                     CurlSendFile( const std::string& sFileFullPath, const std::string& sArg );
    }
}

#endif // USING_CURL