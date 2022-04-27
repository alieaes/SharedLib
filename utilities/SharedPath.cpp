#include "SharedPath.h"
#include "SharedString.h"

#include "Shared_Defs.h"

#include <filesystem>
#include <algorithm>

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif

namespace Shared
{
    namespace Path
    {
        std::wstring GetCurrentPath( bool bIncludeSeparate /*= false*/ )
        {
            std::wstring ret;
            wchar_t result[ MAX_PATH ];
            std::wstring sCurrentPath = std::wstring( result, GetModuleFileName( NULL, result, MAX_PATH ) );
            sCurrentPath = ConvertSeparator( sCurrentPath );

            int find = sCurrentPath.rfind( L'/' );

            ret = sCurrentPath.substr( 0, find );
            if( bIncludeSeparate == true )
                ret = ret + L'/';

            return ret;
        }

        std::wstring ConvertSeparator( const std::wstring& sStr )
        {
            std::wstring sPath = sStr;
            std::replace( sPath.begin(), sPath.end(), L'\\', L'/' );
            return sPath;
        }

        bool IsExistFile( const std::wstring& sPath )
        {
            return std::filesystem::exists( sPath );
        }
#ifdef USING_QTLIB
        bool IsExistFile( const QString& sPath )
        {
            return std::filesystem::exists( sPath.toStdWString() );
        }
#endif
        std::wstring SeparateFileNameToExts( const std::wstring& sFileFullPath )
        {
            // TODO : 현재 확장자가 없는 파일은 고려되고 있지 않음 추가 필요
            if( sFileFullPath.empty() == true )
                return std::wstring();

            std::wstring sFileName = sFileFullPath;
            int find = sFileName.rfind( L'.' );

            return sFileName.substr( 0, find );
        }

        std::wstring GetFileExts( const std::wstring& sFileFullPath )
        {
            // TODO : 현재 확장자가 없는 파일은 고려되고 있지 않음 추가 필요
            if( sFileFullPath.empty() == true )
                return std::wstring();

            std::wstring sExts = sFileFullPath;
            int find = sExts.rfind( L'.' );
            return sExts.substr( find, sExts.length() - find );
        }

        uintmax_t GetFileSize( const std::wstring& sPath )
        {
            return std::filesystem::file_size( sPath );
        }

        std::wstring AppendSeparator( const std::wstring& sPath )
        {
            std::wstring sConvertPath = ConvertSeparator( sPath );
            if( String::EndsWith( sConvertPath, L"/" ) == false )
                return ( sPath + L"/" );
            else
                return sPath;
        }
    }
}