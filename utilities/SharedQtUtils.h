#ifndef __HDR_SHARED_QTUTILS__
#define __HDR_SHARED_QTUTILS__
#endif

#include "stdafx.h"

#include <string>
#include <Windows.h>

#ifdef USING_QTLIB
#include <qdatetime.h>
#include <qstring.h>
#endif // USING_QTLIB

namespace Shared
{
    namespace QtUtils
    {
#ifdef USING_QTLIB
        bool CreateFileFromQTResource( const QString& createFilePath, const QString& qtResourcePath );
#endif
    }
}