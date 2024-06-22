
#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object {
private:
    Object* next;

public:
    Object* GetNext(void) const {
        return next;
    }

    void SetNext(Object* next_) {
        next = next_;
    }

    virtual ~Object();
    virtual void Initialize(void) = 0;
};

#endif // __OBJECT_H__
