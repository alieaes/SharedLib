﻿#ifndef __HDR_SHARED_PATH__
#define __HDR_SHARED_PATH__
#endif

#include <string>
#include <Windows.h>

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif // USING_QTLIB

namespace Shared
{
    namespace Path
    {
        std::wstring                 GetCurrentPath();

        std::wstring                 ConvertSeparator( const std::wstring& sStr );

        bool                         IsExistFile( const std::wstring& sPath );

        std::wstring                 SeparateFileNameToExts( const std::wstring& sFileFullPath );

        std::wstring                 GetFileExts( const std::wstring& sFileFullPath );

        uintmax_t                    GetFileSize( const std::wstring& sPath );

    }
}