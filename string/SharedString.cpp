#include "stdafx.h"
#include <locale>
#include <codecvt>
#include <algorithm>

#include "SharedString.h"

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif

namespace Shared
{
    namespace String
    {
        std::wstring s2ws( const std::string& str )
        {
            using convert_typeX = std::codecvt_utf8<wchar_t>;
            std::wstring_convert<convert_typeX, wchar_t> converterX;

            return converterX.from_bytes( str );
        }

        std::string ws2s( const std::wstring& wstr )
        {
            using convert_typeX = std::codecvt_utf8<wchar_t>;
            std::wstring_convert<convert_typeX, wchar_t> converterX;

            return converterX.to_bytes( wstr );
        }
    }
}
