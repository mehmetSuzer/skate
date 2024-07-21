
#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object {
private:
    Object* next;

public:
    inline Object* GetNext(void) const noexcept {
        return next;
    }

    inline void SetNext(Object* next_) noexcept {
        next = next_;
    }

    virtual ~Object() noexcept {}
    virtual void Initialize(void) noexcept = 0;
};

#endif // __OBJECT_H__
