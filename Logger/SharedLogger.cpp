#include "stdafx.h"
#include "SharedLogger.h"

#include "fileManager/SharedFileManager.h"
#include "utilities/SharedPath.h"
#include "string/SharedString.h"

#include "Shared_Defs.h"

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif

using namespace Shared::Logger;
using namespace Shared::FileManager;
using namespace Shared::Path;

void Log::init( TyLogger tyLogger )
{
    _isFileLogging = tyLogger.isFileLogging;

    if( _isFileLogging == true )
    {
        FileMgr* stFileMgr = TyStFileMgr::GetInstance();

        FILEMGR fileMgr;
        fileMgr.sUnique = L"logger";
        fileMgr.sFileName = L"A2I-SVC";
        fileMgr.sFilePath = GetCurrentPath();
        fileMgr.isUseAsync = true;

        stFileMgr->InitFileMgr( fileMgr );
    }
}

void Log::Debug( std::string LOGTYPE, const char* fileName, int codeLine, std::string format )
{
#ifdef USING_QTLIB
    QDateTime dtNow = QDateTime::currentDateTime();
    QString sCurrentTime = dtNow.toString( DEFAULT_TIME_STRING );
    std::string msg = fmt::format( "[{}] [{}] ({}:{}) {} \n", sCurrentTime.toStdString(), LOGTYPE, strrchr( fileName, '\\' ) ? strrchr( fileName, '\\' ) + 1 : fileName, codeLine, format );
#else
    time_t now = time( 0 );
    struct tm  tstruct;
    char       timeForm[ 80 ];
    tstruct = *localtime( &now );
    strftime( timeForm, sizeof( timeForm ), "%Y-%m-%d %X", &tstruct ); // YYYY-MM-DD.HH:mm:ss
    std::string msg = fmt::format( "[{}] [{}] ({}:{}) {} \n", timeForm, LOGTYPE, strrchr( fileName, '\\' ) ? strrchr( fileName, '\\' ) + 1 : fileName, codeLine, format );
#endif // USING_QTLIB

    OutputDebugStringA( ( LPCSTR )msg.c_str() );

    if( _isFileLogging )
    {
        FileMgr* stFileMgr = TyStFileMgr::GetInstance();
        stFileMgr->WriteFileContents( L"logger", Shared::String::s2ws( msg ) );
    }
}

void Log::Recode( const char* LOGTYPE, const char* fileName, int codeLine, std::string format )
{
}
