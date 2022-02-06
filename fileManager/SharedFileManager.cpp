#include "stdafx.h"

#include "SharedFileManager.h"
#include "SharedPath.h"
#include "Shared_Defs.h"
#include "string/SharedString.h"

#include <thread>
#include <fstream>

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

bool FileMgr::InitFileMgr( FILEMGR fileMgr )
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

void FileMgr::WriteFileContents( FILE_UNIQUE_NAME sUnique, std::wstring sContents )
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

FILEMGR FileMgr::retrieveFileMgr( FILE_UNIQUE_NAME sUnique )
{
    if( _mapFileMgr.count( sUnique ) == 0 )
        return FILEMGR();

    return _mapFileMgr[ sUnique ];
}

void FileMgr::AsyncFileWrite( LPVOID lpParam )
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

void FileMgr::enQueueItem( FILEITEM item )
{
    std::lock_guard< std::mutex > lock( _mutex );
    _queue.push( item );
}

FILEITEM FileMgr::deQueueItem()
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

void FileMgr::writeContents( FILE_UNIQUE_NAME sUnique, std::wstring sContents )
{
    FILEMGR fileMgr = retrieveFileMgr( sUnique );

    if( fileMgr.isValid() == false )
        return;

    std::ofstream ofs( fileMgr.sFileFullPath, std::ios_base::out | std::ios_base::app );

    if( ofs.fail() == true )
    {
        //로깅
    }

    ofs << Shared::String::ws2s( sContents );

    ofs.close();
}
