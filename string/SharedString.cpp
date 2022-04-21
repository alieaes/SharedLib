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

        bool EndsWith( const std::string& sFullString, const std::string& sEnds )
        {
            if( sFullString.length() >= sEnds.length() )
            {
                return ( 0 == sFullString.compare( sFullString.length() - sEnds.length(), sEnds.length(), sEnds ) ); //fullString의 길이에서 ending의 길이만큼 뺀 위치부터 같은지 검사
            }
            else
            {
                //fullString의 길이보다 ending의 길이가 긴 경우 -> 항상 거짓
                return false;
            }
        }

        bool EndsWith( const std::wstring& sFullString, const std::wstring& sEnds )
        {
            if( sFullString.length() >= sEnds.length() )
            {
                return ( 0 == sFullString.compare( sFullString.length() - sEnds.length(), sEnds.length(), sEnds ) ); //fullString의 길이에서 ending의 길이만큼 뺀 위치부터 같은지 검사
            }
            else
            {
                //fullString의 길이보다 ending의 길이가 긴 경우 -> 항상 거짓
                return false;
            }
        }
    }
}
