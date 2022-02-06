#ifndef __HDR_SHARED_FILEMGR__
#define __HDR_SHARED_FILEMGR__
#endif

#include "Singleton.h"
#include <string>
#include <Windows.h>
#include <queue>
#include <mutex>

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif // USING_QTLIB

namespace Shared
{
    namespace FileManager
    {
        typedef std::wstring FILE_UNIQUE_NAME;

        typedef struct _FILEMGR
        {
            std::wstring       sUnique;

            std::wstring       sFileName;
            std::wstring       sFilePath;
            std::wstring       sFileFullPath;

            int                nMaxFileSize  = 50;
            int                nMaxFileCnt   = 5;

            bool               isUseCompress = false;
            bool               isUseAsync    = false;

            int                nMaxCompressFileCnt = 5;

            bool isValid()
            {
                if( sUnique.empty() == false && sFileName.empty() == false && sFilePath.empty() == false && sFileFullPath.empty() == false )
                    return true;
                else
                    return false;
            }
        } FILEMGR;

        typedef struct _FILEITEM
        {
            FILE_UNIQUE_NAME   sUnique;
            std::wstring       sContents;

            bool isValid()
            {
                if( sUnique.empty() == false && sContents.empty() == false )
                    return true;
                else
                    return false;
            }
        } FILEITEM;

        class FileMgr
        {
        public:
            FileMgr();
            ~FileMgr();

            bool                                               InitFileMgr( FILEMGR fileMgr );
            void                                               WriteFileContents( FILE_UNIQUE_NAME sUnique, std::wstring sContents );
            static void                                        AsyncFileWrite( LPVOID lpParam );

            bool                                               IsStop() { return _isStop; }
        private:
            FILEMGR                                            retrieveFileMgr( FILE_UNIQUE_NAME sUnique );

            void                                               writeContents( FILE_UNIQUE_NAME sUnique, std::wstring sContents );

            void                                               enQueueItem( FILEITEM item );
            FILEITEM                                           deQueueItem();

            std::unordered_map< std::wstring, FILEMGR >        _mapFileMgr;
            std::thread                                        _thMain;
            std::queue< FILEITEM >                             _queue;
            std::mutex                                         _mutex;

            bool                                               _isStop     = false;
        };
    }
}

typedef Shared::Singletons::Singleton<Shared::FileManager::FileMgr> TyStFileMgr;