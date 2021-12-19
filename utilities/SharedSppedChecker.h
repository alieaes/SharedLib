#ifndef __HDR_SHARED_CHECKER__
#define __HDR_SHARED_CHECKER__

#pragma once

#include "Singleton.h"

#include <formatter/format.h>
#include <string>
#include <time.h>
#include <Windows.h>
#include <unordered_map>
#include <chrono>

/*
* 사용방법 : 측정하고 싶은 곳에 CHECK_TIME_START로 측정 시작
*            중간에서 측정하고 싶은 곳에서 INTERIM 함수 사용, 종료 시 END 함수 사용
*/

#define CHECK_TIME_START                                                                                                                     \
    TyStChcker::GetInstance()->CheckTimeStart( TyStChcker::GetInstance()->CreateKeyName( GetCurrentThreadId(), __FUNCTION__ ) );             \

#define CHECK_TIME_INTERIM                                                                                                                   \
    TyStChcker::GetInstance()->CheckTimeInterimFindings( TyStChcker::GetInstance()->CreateKeyName( GetCurrentThreadId(), __FUNCTION__ ) );   \

#define CHECK_TIME_END                                                                                                                       \
    TyStChcker::GetInstance()->CheckTimeEnd( TyStChcker::GetInstance()->CreateKeyName( GetCurrentThreadId(), __FUNCTION__ ) );               \

namespace Shared
{
    namespace SpeedChecker
    {
        class Checker
        {
        public:
            void                                               CheckTimeStart( std::wstring sKey );

            double                                             CheckTimeInterimFindings( std::wstring sKey );

            double                                             CheckTimeEnd( std::wstring sKey );

            std::wstring                                       CreateKeyName( DWORD dwThreadId, char* sFunctionName );
        private:
            std::unordered_map< std::wstring, std::chrono::system_clock::time_point >            _mapCheckTime;

            std::unordered_map< std::wstring, std::chrono::system_clock::time_point >            _mapInterimFindings;
        };
    }
}

typedef Shared::Singletons::Singleton<Shared::SpeedChecker::Checker> TyStChcker;

#endif