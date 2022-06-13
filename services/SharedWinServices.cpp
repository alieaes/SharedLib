#include "SharedPath.h"
#include "SharedString.h"

#include "Shared_Defs.h"

#include <filesystem>
#include <algorithm>
#include <QApplication>

#ifdef USING_QTLIB
#include <qdatetime.h>
#include "SharedWinServices.h"
#endif

namespace Shared
{
    namespace services
    {
        bool IsExistService()
        {
            return true;
        }

        bool IsRunningService()
        {
            return true;
        }

        CService::CService()
        {
            scMgr = ::OpenSCManagerW( NULL, NULL, SC_MANAGER_ALL_ACCESS );

            if( scMgr == NULL )
            {
                DWORD  dwError = ::GetLastError();
            }
        }
    }
}


