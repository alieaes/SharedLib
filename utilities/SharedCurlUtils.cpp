#include "Shared_Defs.h"
#include "SharedCurlUtils.h"
#include "SharedPath.h"
#include "SharedString.h"

#include "format.h"

#include <regex>
#include <winsock.h>
#include <iostream>
#include <fstream>

#ifdef USING_CURL
#include <curl.h>
#endif // USING_CURL

#ifdef USING_QTLIB
#endif

#pragma comment( lib, "ws2_32.lib" )

#ifdef USING_CURL

namespace Shared
{
    namespace Curl
    {
        bool CurlSendFile( const std::string& sFileFullPath, const std::string& sArg )
        {
            bool isSuccess = false;

            do
            {
                std::ifstream file( sFileFullPath, std::ios::in | std::ios::binary | std::ios::ate );
                int nSize = 0;
                char* memblock;

                if( file.is_open() == true )
                {
                    nSize = file.tellg();
                    memblock = new char[ nSize ];
                    file.seekg( 0, std::ios::beg );
                    file.read( memblock, nSize );
                    file.close();
                }

                CURL* curl;
                curl_global_init( CURL_GLOBAL_ALL );
                CURLcode res;

                std::string url = fmt::format( "http://forbiddensite.duckdns.org/api.php?{}", sArg );

                struct curl_httppost* formpost = NULL;
                struct curl_httppost* lastptr = NULL;
                struct curl_slist* headerlist = NULL;
                static const char buf[] = "Expect:";

                auto sFileName = Shared::Path::GetFileName( Shared::String::s2ws( sFileFullPath ) );

                curl_formadd( &formpost,
                              &lastptr,
                              CURLFORM_COPYNAME, "cache-control:",
                              CURLFORM_COPYCONTENTS, "no-cache",
                              CURLFORM_END );

                curl_formadd( &formpost,
                              &lastptr,
                              CURLFORM_COPYNAME, "content-type:",
                              CURLFORM_COPYCONTENTS, "multipart/form-data",
                              CURLFORM_END );

                curl_formadd( &formpost, &lastptr,
                              CURLFORM_COPYNAME, "file",
                              CURLFORM_BUFFER, Shared::String::ws2s( sFileName ).c_str(),
                              CURLFORM_BUFFERPTR, memblock,
                              CURLFORM_BUFFERLENGTH, nSize,
                              CURLFORM_END );

                curl = curl_easy_init();
                if( curl )
                {
                    headerlist = curl_slist_append( headerlist, buf );
                    curl_easy_setopt( curl, CURLOPT_URL, url.data() );
                    curl_easy_setopt( curl, CURLOPT_HTTPPOST, formpost );

                    res = curl_easy_perform( curl );
                    if( res != CURLE_OK )
                    {
                        fprintf( stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror( res ) );
                    }
                    curl_easy_cleanup( curl );
                }
                curl_global_cleanup();

                delete[] memblock;

                isSuccess = true;

            } while( false );

            return isSuccess;
        }
    }
}

#endif // USING_CURL