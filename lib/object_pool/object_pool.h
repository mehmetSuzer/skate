
#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include <type_traits>
#include <stddef.h>
#include <stdint.h>
#include "exception.h"
#include "object.h"

template<typename T>
class ObjectPool {
    static_assert(std::is_base_of<Object, T>::value, "Template parameter T must inherit from Object!");

private:
    static const uint32_t poolSize = 3000;
    T pool[poolSize];

    uint32_t availableCount;
    T* firstAvailable;

public:
    ObjectPool();

    uint32_t GetAvailableCount(void) const {
        return availableCount;
    }

    T* Get(void);
    void Release(T* t);
};

#endif // __OBJECT_POOL_H__
