
#include "object_pool.h"

template<typename T>
 ObjectPool<T>::ObjectPool() {
    for (uint32_t i = 0; i < poolSize-1; i++) {
        pool[i].SetNext(pool+(i+1));
    }
    pool[poolSize-1].SetNext(NULL);
    firstAvailable = pool;
    availableCount = poolSize;
}

template<typename T>
T* ObjectPool<T>::Get(void) {
    if (firstAvailable == NULL) {
        throw Exception("Object Pool is Full!");
    }

    T* t = firstAvailable;
    firstAvailable = t->GetNext();
    t->Initialize();
    availableCount--;
    return t;
}

template<typename T>
void ObjectPool<T>::Release(T* t) {
    t->SetNext(firstAvailable);
    firstAvailable = t;
    availableCount++;
}
