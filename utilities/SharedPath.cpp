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
            std::wstring sCurrentPath = std::filesystem::current_path();
            std::replace( sCurrentPath.begin(), sCurrentPath.end(), L'\\', L'/' );

            return sCurrentPath;
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
    }
}