#include "stdafx.h"

#ifdef USING_QTLIB
#include <qdatetime.h>
#include "string.h"
#endif

namespace Shared
{
    namespace String
    {
        std::wstring StringToWString( std::string str )
        {
            std::wstring sWstr;
            sWstr.assign( str.begin(), str.end() );

            return sWstr;
        }
    }
}
