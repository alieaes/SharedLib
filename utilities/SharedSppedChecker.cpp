#include "stdafx.h"
#include "Logger/SharedLogger.h"
#include "SharedSppedChecker.h"
#include "string/string.h"

#ifdef USING_QTLIB
#include <qdatetime.h>
#endif

using namespace Shared::SpeedChecker;

std::string logger = "TIMECHECKER";

void Checker::CheckTimeStart( std::wstring sKey )
{
    std::chrono::system_clock::time_point tmStart = std::chrono::system_clock::now();

    if( _mapCheckTime.count( sKey ) <= 0 )
    {
        _mapCheckTime[ sKey ] = tmStart;
    }
    else
    {
        // 스레드 번호와 함수 이름을 조합했는데 있는 경우가 있...나?
        // override 한 곳에서 발생 할 수는 있을 법함, 만약 발생한다면 저장방식 변경 필요
        assert( false );
    }

#ifdef USING_LOGGER
    LOGD( logger, "CHECK TIME START" );
#endif // USING_LOGGER
}

double Checker::CheckTimeInterimFindings( std::wstring sKey )
{
    if( _mapCheckTime.count( sKey ) <= 0 )
        return 0;

    std::chrono::system_clock::time_point tmNow = std::chrono::system_clock::now();
    std::chrono::duration<double> sec;

    /*
    * 중간에 체크한 경우가 존재한다면 InterimFindings에 값이 존재함, 중간 체크 시간 ~ 호출된 시점 까지의 시간 차를 구함
    * 존재하지 않는다면 시작 시간 ~ 호출된 시점의 시간을 구하고, 호출된 시점을 백업함
    */

    if( _mapInterimFindings.count( sKey ) > 0 )
    {
        sec = tmNow - _mapInterimFindings[ sKey ];
    }
    else
    {
        sec = tmNow - _mapCheckTime[ sKey ];
        _mapInterimFindings[ sKey ] = tmNow;
    }

#ifdef USING_LOGGER
    LOGD( logger, "CHECK TIME INTERIM = {} second", sec.count() );
#endif // USING_LOGGER

    return sec.count();
}

std::wstring Checker::CreateKeyName( DWORD dwThreadId, char* sFunctionName )
{
    std::string str( sFunctionName );
    std::wstring sKey = Shared::String::StringToWString( str ) + std::to_wstring( dwThreadId );
    return sKey;
}

double Checker::CheckTimeEnd( std::wstring sKey )
{
    if( _mapCheckTime.count( sKey ) <= 0 )
        return 0;

    std::chrono::system_clock::time_point tmNow = std::chrono::system_clock::now();
    std::chrono::duration<double> sec = tmNow - _mapCheckTime[ sKey ];

    _mapCheckTime.erase( sKey );

#ifdef USING_LOGGER
    LOGD( logger, "CHECK TIME END = {} second", sec.count() );
#endif // USING_LOGGER

    return sec.count();
}
