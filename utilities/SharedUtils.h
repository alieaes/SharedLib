#ifndef __HDR_SHARED_UTILS__
#define __HDR_SHARED_UTILS__
#endif

#include <string>
#include <Windows.h>

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif // USING_QTLIB

namespace Shared
{
    namespace Utils
    {
        bool                     ValidateIpAddress( const std::string& sAddress );

        std::string              ConvertDomainToIp( const std::string& sDomain );
    }
}