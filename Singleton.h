#ifndef __HDR_SINGLETON__
#define __HDR_SINGLETON__

#include <mutex>

#include "Shared_Defs.h"

namespace Shared
{
    namespace Singletons
    {
        template < typename T >
        class Singleton
        {
        public:
            Singleton() {}

            static T* GetInstance()
            {
                if( _instance == NULLPTR )
                    std::call_once( _flag, []() { _instance = new T; } );

                return _instance;
            }

            static void DestroyInstance()
            {
                if( _instance != NULLPTR )
                    delete _instance;
            }

        private:
            static T* _instance;
            static std::once_flag _flag;

        };

        template < typename T >
        T* Singleton<T>::_instance = NULLPTR;

        template < typename T >
        std::once_flag Singleton<T>::_flag;
    }
}

#endif
