#ifndef __HDR_SHARED_STRING__
#define __HDR_SHARED_STRING__

#include "Singleton.h"
#include <formatter/format.h>
#include <string>
#include <time.h>
#include <Windows.h>

#ifdef USING_QTLIB
#include <qstring.h>
#endif // USING_QTLIB


namespace Shared
{
    namespace String
    {
        std::wstring                 s2ws( const std::string& str );
        std::string                  ws2s( const std::wstring& wstr );

        bool                         EndsWith( const std::string& sFullString, const std::string& sEnds );
        bool                         EndsWith( const std::wstring& sFullString, const std::wstring& sEnds );
    }
}

#endif