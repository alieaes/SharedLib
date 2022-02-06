#include "stdafx.h"
#include "SharedPath.h"
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
        std::wstring GetCurrentPath()
        {
            wchar_t result[ MAX_PATH ];
            std::wstring sCurrentPath = std::wstring( result, GetModuleFileName( NULL, result, MAX_PATH ) );
            sCurrentPath = ConvertSeparator( sCurrentPath );

            int find = sCurrentPath.rfind( L'/' );

            return sCurrentPath.substr( 0, find );
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

        std::wstring SeparateFileNameToExts( const std::wstring& sFileFullPath )
        {
            // TODO : ���� Ȯ���ڰ� ���� ������ ����ǰ� ���� ���� �߰� �ʿ�
            if( sFileFullPath.empty() == true )
                return std::wstring();

            std::wstring sFileName = sFileFullPath;
            int find = sFileName.rfind( L'.' );

            return sFileName.substr( 0, find );
        }

        std::wstring GetFileExts( const std::wstring& sFileFullPath )
        {
            // TODO : ���� Ȯ���ڰ� ���� ������ ����ǰ� ���� ���� �߰� �ʿ�
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
    }
}