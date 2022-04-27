#include "SharedLibInit.h"

#include "SharedLogger.h"

#include <iostream>

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
using namespace Shared::String;

void Shared::Logger::Log::init(TyLogger tyLogger)
{
    _isFileLogging = tyLogger.isFileLogging;

    if( _isFileLogging == true )
    {
        FileMgr* stFileMgr = TyStFileMgr::GetInstance();

        FILEMGR fileMgr;
        fileMgr.sUnique = L"logger";
        fileMgr.sFileName = L"SVC";
        fileMgr.sFilePath = GetCurrentPath();
        fileMgr.isUseAsync = true;
        fileMgr.isUseFileNumbering = true;

        stFileMgr->InitFileMgr( fileMgr );
    }
}

void Shared::Logger::Log::Debug( std::string LOGTYPE, const char* fileName, int codeLine, std::string format )
{
#ifdef USING_QTLIB
    QDateTime dtNow = QDateTime::currentDateTime();
    QString sCurrentTime = dtNow.toString( DEFAULT_TIME_STRING );
    std::string msg = std::format( "[{}] [{}] ({}:{}) {} \n", sCurrentTime.toStdString(), LOGTYPE, strrchr( fileName, '\\' ) ? strrchr( fileName, '\\' ) + 1 : fileName, codeLine, format );
#else
    time_t now = time( 0 );
    struct tm  tstruct;
    char       timeForm[ 80 ];
    localtime_s( &tstruct, &now );
    strftime( timeForm, sizeof( timeForm ), "%Y-%m-%d %X", &tstruct ); // YYYY-MM-DD.HH:mm:ss

    std::string msg = std::format( "[{}] [{}] ({}:{}) {} \n", timeForm, LOGTYPE, strrchr( fileName, '\\' ) ? strrchr( fileName, '\\' ) + 1 : fileName, codeLine, format );
#endif // USING_QTLIB

    static DWORD dwNumberOfCharsWritten = 0;
    OutputDebugStringA( ( LPCSTR )msg.c_str() );
    WriteConsoleA( GetStdHandle( STD_OUTPUT_HANDLE ), msg.c_str(), ( DWORD )msg.size(), &dwNumberOfCharsWritten, NULL );

    if( _isFileLogging )
    {
        FileMgr* stFileMgr = TyStFileMgr::GetInstance();
        stFileMgr->WriteFileContents( L"logger", Shared::String::s2ws( msg ) );
    }
}

void Shared::Logger::Log::Debug( std::string LOGTYPE, const char* fileName, int codeLine, std::wstring format )
{
#ifdef USING_QTLIB
    QDateTime dtNow = QDateTime::currentDateTime();
    QString sCurrentTime = dtNow.toString( DEFAULT_TIME_STRING );
    std::wstring msg = std::format( L"[{}] [{}] ({}:{}) {} \n", sCurrentTime.toStdString(), LOGTYPE, strrchr( fileName, '\\' ) ? strrchr( fileName, '\\' ) + 1 : fileName, codeLine, format );
#else
    time_t now = time( 0 );
    struct tm  tstruct;
    char       timeForm[ 80 ];
    localtime_s( &tstruct, &now );
    strftime( timeForm, sizeof( timeForm ), "%Y-%m-%d %X", &tstruct ); // YYYY-MM-DD.HH:mm:ss

    std::wstring msg = std::format( L"[{}] [{}] ({}:{}) {} \n", c2wc( timeForm ), s2ws( LOGTYPE ), c2wc( strrchr( fileName, '\\' ) ) ? c2wc( strrchr( fileName, '\\' ) ) + 1 : c2wc( fileName ), codeLine, format );
#endif // USING_QTLIB

    static DWORD dwNumberOfCharsWritten = 0;
    OutputDebugStringW( ( LPCWSTR )msg.c_str() );
    WriteConsoleW( GetStdHandle( STD_OUTPUT_HANDLE ), msg.c_str(), ( DWORD )msg.size(), &dwNumberOfCharsWritten, NULL );

    if( _isFileLogging )
    {
        FileMgr* stFileMgr = TyStFileMgr::GetInstance();
        stFileMgr->WriteFileContents( L"logger", msg );
    }
}

void Shared::Logger::Log::ConsolePrint( const char* fileName, int codeLine, std::wstring format )
{
    std::wstring msg = format;
    static DWORD dwNumberOfCharsWritten = 0;
    WriteConsoleW( GetStdHandle( STD_OUTPUT_HANDLE ), msg.c_str(), ( DWORD )msg.size(), &dwNumberOfCharsWritten, NULL );
}

void Shared::Logger::Log::Recode( const char* LOGTYPE, const char* fileName, int codeLine, std::string format )
{
}
