#include "SharedLibInit.h"

#include "SharedLogger.h"

#include <iostream>

#ifdef USGIN_LOGGER_FILEMGR
#include "fileManager/SharedFileManager.h"
#endif
#include "utilities/SharedPath.h"
#include "string/SharedString.h"

#include "Shared_Defs.h"

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif

using namespace Shared::Logger;
using namespace Shared::Path;
using namespace Shared::String;
#ifdef USGIN_LOGGER_FILEMGR
using namespace Shared::FileManager;
#endif

void Shared::Logger::Log::init(TyLogger tyLogger)
{
    _isFileLogging = tyLogger.isFileLogging;

#ifdef USING_LOGGER_FILEMGR
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
#endif
}

void Shared::Logger::Log::LogCase( TyEnLogger eLogType, const char* fileName, int codeLine, std::string format )
{
    switch (eLogType)
    {
    case LOGGER_NONE:
        {
        break;
        }
    case LOGGER_DEBUG:
    case LOGGER_LIBS:
        {
        Logging( fileName, codeLine, format );
        break;
        }
    case LOGGER_CONSOLE:
        {
        ConsolePrint( format );
        break;
        }
    }
}

void Log::LogCase( TyEnLogger eLogType, const char* fileName, int codeLine, std::wstring format )
{
    switch( eLogType )
    {
        case LOGGER_NONE:
        {
            break;
        }
        case LOGGER_DEBUG:
        case LOGGER_LIBS:
        {
            Logging( fileName, codeLine, format );
            break;
        }
        case LOGGER_CONSOLE:
        {
            ConsolePrint( format );
            break;
        }
    }
}

void Shared::Logger::Log::Logging( const char* fileName, int codeLine, std::string format )
{
#ifdef USING_QTLIB
    QDateTime dtNow = QDateTime::currentDateTime();
    QString sCurrentTime = dtNow.toString( DEFAULT_TIME_STRING );
    std::string msg = std::format( "[{}] [{}] ({}:{}) {} \n", sCurrentTime.toStdString(), "LEVEL", strrchr(fileName, '\\') ? strrchr(fileName, '\\') + 1 : fileName, codeLine, format);
#else
    time_t now = time( 0 );
    struct tm  tstruct;
    char       timeForm[ 80 ];
    localtime_s( &tstruct, &now );
    strftime( timeForm, sizeof( timeForm ), "%Y-%m-%d %X", &tstruct ); // YYYY-MM-DD.HH:mm:ss

    std::string msg = std::format( "[{}] [{}] ({}:{}) {} \n", timeForm, "LEVEL", strrchr( fileName, '\\' ) ? strrchr( fileName, '\\' ) + 1 : fileName, codeLine, format );
#endif // USING_QTLIB

    static DWORD dwNumberOfCharsWritten = 0;
#ifdef USING_SHARED_LOGGER
    OutputDebugStringA( ( LPCSTR )msg.c_str() );
    WriteConsoleA( GetStdHandle( STD_OUTPUT_HANDLE ), msg.c_str(), ( DWORD )msg.size(), &dwNumberOfCharsWritten, NULL );

#ifdef USING_LOGGER_FILEMGR
    if( _isFileLogging )
    {
        FileMgr* stFileMgr = TyStFileMgr::GetInstance();
        stFileMgr->WriteFileContents( L"logger", Shared::String::s2ws( msg ) );
    }
#endif
#endif
}

void Shared::Logger::Log::Logging( const char* fileName, int codeLine, std::wstring format )
{
#ifdef USING_QTLIB
    QDateTime dtNow = QDateTime::currentDateTime();
    QString sCurrentTime = dtNow.toString( DEFAULT_TIME_STRING );
    std::wstring msg = std::format( L"[{}] [{}] ({}:{}) {} \n", sCurrentTime.toStdWString(), L"LEVEL", c2wc( strrchr( fileName, '\\' ) ) ? c2wc( strrchr( fileName, '\\' ) ) + 1 : c2wc( fileName ), codeLine, format );
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

#ifdef USING_LOGGER_FILEMGR
    if( _isFileLogging )
    {
        FileMgr* stFileMgr = TyStFileMgr::GetInstance();
        stFileMgr->WriteFileContents( L"logger", msg );
    }
#endif
}

void Shared::Logger::Log::ConsolePrint( std::wstring format )
{
    std::wstring msg = format;
    static DWORD dwNumberOfCharsWritten = 0;
    WriteConsoleW( GetStdHandle( STD_OUTPUT_HANDLE ), msg.c_str(), ( DWORD )msg.size(), &dwNumberOfCharsWritten, NULL );
}

void Shared::Logger::Log::ConsolePrint( std::string format )
{
    std::string msg = format;
    static DWORD dwNumberOfCharsWritten = 0;
    WriteConsoleW( GetStdHandle( STD_OUTPUT_HANDLE ), msg.c_str(), ( DWORD )msg.size(), &dwNumberOfCharsWritten, NULL );
}