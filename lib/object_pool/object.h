
#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object {
private:
    Object* next;

public:
    inline Object* GetNext(void) const {
        return next;
    }

    inline void SetNext(Object* next_) {
        next = next_;
    }

    virtual ~Object() {}
    virtual void Initialize(void) = 0;
};

#endif // __OBJECT_H__
