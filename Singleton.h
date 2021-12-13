#ifndef __HDR_SINGLETON__
#define __HDR_SINGLETON__

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
                    _instance = new T;

                return _instance;
            }

            static void DestroyInstance()
            {
                if( _instance != NULLPTR )
                    delete _instance;
            }

        private:
            static T* _instance;
        };

        template < typename T >
        T* Singleton<T>::_instance = NULLPTR;
    }
}

#endif
