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
    namespace winAPI
    {
        std::wstring                 GetPCName();
        unsigned long                GetCurrentKeyBoardLang();
        bool                         IsCurrentKoreanLang();
    }
}