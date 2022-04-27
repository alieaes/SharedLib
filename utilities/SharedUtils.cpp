#include "Shared_Defs.h"
#include "SharedUtils.h"

#include <regex>
#include <winsock.h>

#ifdef USING_QTLIB
#endif

#pragma comment( lib, "ws2_32.lib" )

namespace Shared
{
    namespace Utils
    {
        bool ValidateIpAddress( const std::string& sAddress )
        {
            bool isValidate = false;

            do
            {
                std::string strRegExpIP = "^(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-1]?[0-9]?[0-9]?)\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-1]?[0-9]?[0-9]?)\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-1]?[0-9]?[0-9]?)\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-1]?[0-9]?[0-9]?)";
                std::regex rxIP( strRegExpIP );

                if( std::regex_match( sAddress.c_str(), rxIP ) == false )
                {
                    //ConvertDomainToIp( sAddress );
                    //
                    //if( std::regex_match( ConvertDomainToIp( sAddress ), rxIP ) == false )
                    //    break;
                }

                isValidate = true;

            } while( false );

            return isValidate;
        }

        std::string ConvertDomainToIp( const std::string& sDomain )
        {
            WSADATA wsaData;
            WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
            
            std::string sRet;
            in_addr in;
            LPHOSTENT host_entry = gethostbyname( sDomain.c_str() );
            
            if( host_entry != NULL )
            {
                in.s_addr = ( ( LPIN_ADDR )host_entry->h_addr )->s_addr;
                sRet = inet_ntoa( in );
            }
            
            WSACleanup();

            return sRet;
        }
    }
}