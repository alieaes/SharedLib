#include "SharedPath.h"
#include "Shared_Defs.h"

#include <filesystem>
#include <algorithm>

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif

namespace Shared
{
    namespace QtUtils
    {
#ifdef USING_QTLIB
        bool CreateFileFromQTResource( const QString& createFilePath, const QString& qtResourcePath )
        {
            bool isSuccess = false;

            do
            {
                Q_ASSERT( createFilePath.isEmpty() == false && qtResourcePath.isEmpty() == false );
                if( createFilePath.isEmpty() == true || qtResourcePath.isEmpty() == true )
                    break;

                QFile resFile( qtResourcePath );
                if( resFile.open( QIODevice::ReadOnly ) == false )
                    break;

                QFileInfo makeFileI( createFilePath );
                if( makeFileI.filePath().isEmpty() == false )
                    QDir().mkpath( makeFileI.absolutePath() );

                QFile makeFile( createFilePath );
                if( makeFile.open( QIODevice::WriteOnly ) == false )
                    break;

                QByteArray readData = resFile.readAll();

                isSuccess = makeFile.write( readData ) == readData.size() ? true : false;

            } while( false );

            return isSuccess;
        }
#endif
    }
}