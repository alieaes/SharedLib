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
    namespace services
    {
        bool                         IsExistService();
        bool                         IsRunningService();

        class CService
        {
        public:
            CService();

        private:
            SC_HANDLE                scMgr;
        };
    }
}