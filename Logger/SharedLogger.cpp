#include "stdafx.h"
#include "SharedLogger.h"

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif

using namespace Shared::Logger;

void Log::Debug( const char* LOGTYPE, const char* fileName, int codeLine, std::string format )
{
#ifdef USING_QTLIB
    QDateTime dtNow = QDateTime::currentDateTime();
    QString sCurrentTime = dtNow.toString( "yyyy-MM-dd HH:mm:ss" );
    std::string msg = fmt::format( "[{}][{}] ({}:{}) {} \n", sCurrentTime.toStdString(), LOGTYPE, strrchr( fileName, '\\' ) ? strrchr( fileName, '\\' ) + 1 : fileName, codeLine, format );
#else
    time_t now = time( 0 );
    struct tm  tstruct;
    char       timeForm[ 80 ];
    tstruct = *localtime( &now );
    strftime( timeForm, sizeof( timeForm ), "%Y-%m-%d %X", &tstruct ); // YYYY-MM-DD.HH:mm:ss
    std::string msg = fmt::format( "[{}][{}] ({}:{}) {} \n", timeForm, LOGTYPE, strrchr( fileName, '\\' ) ? strrchr( fileName, '\\' ) + 1 : fileName, codeLine, format );
#endif // USING_QTLIB

    OutputDebugStringA( ( LPCSTR )msg.c_str() );
}

void Log::Recode( const char* LOGTYPE, const char* fileName, int codeLine, std::string format )
{
}
