#include "SharedPath.h"
#include "SharedString.h"

#include "Shared_Defs.h"

#include <filesystem>
#include <algorithm>

#ifdef USING_QTLIB
#include <qdatetime.h>
#include "SharedWinAPI.h"
#endif

namespace Shared
{
    namespace winAPI
    {
        std::wstring GetPCName()
        {
            wchar_t szTemp[ 1024 ] = { 0, };
            DWORD dwSize = 255;

            GetComputerName( szTemp, &dwSize );

            return szTemp;
        }
    }
}


