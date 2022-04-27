#include <locale>
#include <codecvt>
#include <algorithm>

#include "SharedLibInit.h"

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
            if( str.empty() == true ) 
                return std::wstring();

            int size_needed = MultiByteToWideChar( CP_UTF8, 0, &str[ 0 ], ( int )str.size(), NULL, 0 );
            std::wstring wstrTo( size_needed, 0 );

            MultiByteToWideChar( CP_UTF8, 0, &str[ 0 ], ( int )str.size(), &wstrTo[ 0 ], size_needed );

            return wstrTo;
        }

        wchar_t* c2wc( const char* c )
        {
            int size_needed = MultiByteToWideChar( CP_ACP, 0, c, -1, NULL, NULL );
            wchar_t* wc = new WCHAR[ size_needed ];

            MultiByteToWideChar( CP_UTF8, 0, &c[ 0 ], strlen( c ), &wc[ 0 ], size_needed );

            return wc;
        }

        std::string ws2s( const std::wstring& wstr )
        {
            if( wstr.empty() == true )
                return std::string();

            int size_needed = WideCharToMultiByte( CP_UTF8, 0, &wstr[ 0 ], ( int )wstr.size(), NULL, 0, NULL, NULL );
            std::string strTo( size_needed, 0 );

            WideCharToMultiByte( CP_UTF8, 0, &wstr[ 0 ], ( int )wstr.size(), &strTo[ 0 ], size_needed, NULL, NULL );

            return strTo;
        }

        char* wc2c( const wchar_t* wc )
        {
            int size_needed = WideCharToMultiByte( CP_ACP, 0, wc, -1, NULL, 0, NULL, NULL );
            char* c = new char[ size_needed ];

            WideCharToMultiByte( CP_UTF8, 0, &wc[ 0 ], -1, c, size_needed, NULL, NULL );

            return c;
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
