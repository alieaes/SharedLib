#include "SharedLibInit.h"

#include "SharedFileManager.h"
#include "SharedPath.h"
#include "Shared_Defs.h"
#include "string/SharedString.h"

#include <thread>
#include <fstream>
#include <format>

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif

using namespace Shared::FileManager;

FileMgr::FileMgr()
{
    _thMain = std::thread( AsyncFileWrite, this );
}

FileMgr::~FileMgr()
{
    _isStop = true;

    _thMain.join();
}

bool Shared::FileManager::FileMgr::InitFileMgr(FILEMGR fileMgr)
{
    bool isSuccess = false;
    std::wstring sUnique;

    do
    {
        if( fileMgr.sFileName.empty() == true || fileMgr.sFilePath.empty() == true || fileMgr.sUnique.empty() == true )
            break;

        if( fileMgr.sFileFullPath.empty() == true )
            fileMgr.sFileFullPath = Shared::Path::ConvertSeparator( fileMgr.sFilePath + L"/" + fileMgr.sFileName + L".LOG" );

        if( _mapFileMgr.count( fileMgr.sUnique ) > 0 )
            break;

        _mapFileMgr[ fileMgr.sUnique ] = fileMgr;

        isSuccess = true;

    } while( false );

    return isSuccess;
}

void Shared::FileManager::FileMgr::WriteFileContents( FILE_UNIQUE_NAME sUnique, std::wstring sContents )
{
    if( IsStop() == true )
        return;

    FILEMGR fileMgr = retrieveFileMgr( sUnique );

    if( fileMgr.isValid() == false )
        return;

    FILEITEM item;

    item.sUnique = sUnique;
    item.sContents = sContents;

    if( fileMgr.isUseAsync == true )
    {
        enQueueItem( item );
    }
    else
    {
        writeContents( sUnique, sContents );
    }
}

FILEMGR Shared::FileManager::FileMgr::retrieveFileMgr( FILE_UNIQUE_NAME sUnique )
{
    if( _mapFileMgr.count( sUnique ) == 0 )
        return FILEMGR();

    return _mapFileMgr[ sUnique ];
}

void Shared::FileManager::FileMgr::AsyncFileWrite( LPVOID lpParam )
{
    FileMgr* cFileMgr = ( FileMgr* )lpParam;

    while( cFileMgr->IsStop() == false )
    {
        FILEITEM item = cFileMgr->deQueueItem();

        if( item.isValid() == true )
            cFileMgr->writeContents( item.sUnique, item.sContents );

        SleepEx( 10, false );
    }
}

void Shared::FileManager::FileMgr::enQueueItem( FILEITEM item )
{
    std::lock_guard< std::mutex > lock( _mutex );
    _queue.push( item );
}

FILEITEM Shared::FileManager::FileMgr::deQueueItem()
{
    std::lock_guard< std::mutex > lock( _mutex );
    if( _queue.size() > 0 )
    {
        FILEITEM item = _queue.front();
        _queue.pop();

        return item;
    }
    else
        return FILEITEM();
}

void Shared::FileManager::FileMgr::writeContents( FILE_UNIQUE_NAME sUnique, std::wstring sContents )
{
    FILEMGR fileMgr = retrieveFileMgr( sUnique );

    if( fileMgr.isValid() == false )
        return;

    std::wstring sFileFullPath = fileMgr.sFileFullPath;

    if( fileMgr.isUseFileNumbering == true )
        sFileFullPath = checkFileNumbering( sUnique );

    std::ofstream ofs( sFileFullPath, std::ios_base::out | std::ios_base::app );

    if( ofs.fail() == true )
    {
        //로깅
    }

    ofs << Shared::String::ws2s( sContents );

    ofs.close();
}

std::wstring Shared::FileManager::FileMgr::checkFileNumbering( FILE_UNIQUE_NAME sUnique )
{
    FILEMGR fileMgr = retrieveFileMgr( sUnique );

    if( fileMgr.isValid() == false )
        return std::wstring();

    std::wstring sFileFullPath;

    std::wstring sFileName = Shared::Path::SeparateFileNameToExts( fileMgr.sFileFullPath );
    std::wstring sExts = Shared::Path::GetFileExts( fileMgr.sFileFullPath );

    for( int idx = 0; idx < fileMgr.nMaxFileCnt; ++idx )
    {
        std::wstring sTmp = std::format( L"{}-[{}]{}", sFileName, idx, sExts );

        if( Shared::Path::IsExistFile( sTmp ) == true )
        {
            auto nFileSize = Shared::Path::GetFileSize( sTmp );

            if( nFileSize > ( fileMgr.nMaxFileSize * 1024000 ) )
            {
                // 파일 사이즈가 더 크다면 파일 개수를 확인하고 압축을 진행해야함
                continue;
            }
            else
            {
                sFileFullPath = sTmp;
                break;
            }
        }
        else
        {
            sFileFullPath = sTmp;
            break;
        }
    }

    return sFileFullPath;
}
