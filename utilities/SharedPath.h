#ifndef __HDR_SHARED_PATH__
#define __HDR_SHARED_PATH__
#endif

#include "SharedLibInit.h"

#include <string>
#include <Windows.h>

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif // USING_QTLIB

namespace Shared
{
    namespace Path
    {
        /*
        * NOTE : 모든 Path의 구분자는 '/'로 구분시켜 사용함. 매개변수에 전달된 구분자가 '\'로 전달하더라도 결과물은 '/'로 전달됨
        */
        std::wstring                 GetCurrentPath( bool bIncludeSeparate = false );

        std::wstring                 NormalizeSeparator( const std::wstring& sStr );

        bool                         IsExistFile( const std::wstring& sPath );
#ifdef USING_QTLIB
        bool                         IsExistFile( const QString& sPath );
#endif
        std::wstring                 SeparateFileNameToExts( const std::wstring& sFileFullPath );

        std::wstring                 GetFileExts( const std::wstring& sFileFullPath );

        uintmax_t                    GetFileSize( const std::wstring& sPath );

        std::wstring                 AppendSeparator( const std::wstring& sPath );

        std::wstring                 GetFileName( const std::wstring& sFileFullPath );

        std::wstring                 GetFilePath( const std::wstring& sFileFullPath );
    }
}