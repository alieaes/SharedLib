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
        std::wstring                 StringToWString( std::string str );
    }
}

#endif