
#include "object_pool.h"

namespace skate 
{
    template<typename T>
    ObjectPool<T>::ObjectPool() noexcept 
    {
        for (uint32_t i = 0; i < poolSize-1; i++) 
            pool[i].SetNext(pool+(i+1));

        pool[poolSize-1].SetNext(NULL);
        firstAvailable = pool;
        availableCount = poolSize;
    }

    template<typename T>
    T* ObjectPool<T>::Get(void) noexcept 
    {
        if (firstAvailable == NULL)
            return NULL;

        T* t = firstAvailable;
        firstAvailable = t->GetNext();
        t->Initialize();
        availableCount--;
        return t;
    }

    template<typename T>
    void ObjectPool<T>::Release(T* t) noexcept 
    {
        const T* start = pool;
        const T* end = pool + (poolSize-1);

        if (start > t || t > end) 
            return;
        
        t->SetNext(firstAvailable);
        firstAvailable = t;
        availableCount++;
    }
}
