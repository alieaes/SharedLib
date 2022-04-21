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
        std::wstring                 GetCurrentPath( bool bIncludeSeparate = false );

        std::wstring                 ConvertSeparator( const std::wstring& sStr );

        bool                         IsExistFile( const std::wstring& sPath );
#ifdef USING_QTLIB
        bool                         IsExistFile( const QString& sPath );
#endif
        std::wstring                 SeparateFileNameToExts( const std::wstring& sFileFullPath );

        std::wstring                 GetFileExts( const std::wstring& sFileFullPath );

        uintmax_t                    GetFileSize( const std::wstring& sPath );

        std::wstring                 AppendSeparator( const std::wstring& sPath );
    }
}