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
        // ������ ��ȣ�� �Լ� �̸��� �����ߴµ� �ִ� ��찡 ��...��?
        // override �� ������ �߻� �� ���� ���� ����, ���� �߻��Ѵٸ� ������ ���� �ʿ�
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
    * �߰��� üũ�� ��찡 �����Ѵٸ� InterimFindings�� ���� ������, �߰� üũ �ð� ~ ȣ��� ���� ������ �ð� ���� ����
    * �������� �ʴ´ٸ� ���� �ð� ~ ȣ��� ������ �ð��� ���ϰ�, ȣ��� ������ �����
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
