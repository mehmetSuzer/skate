
#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <stddef.h>
#include <stdint.h>

enum Event {
    EVENT0 = 0,
    EVENT1,
    EVENT2,
    EVENT3,
    EVENT4,
    EVENT5,
    SUBJECT_DEAD,
};

template<typename T>
class Subject;

#define OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION

#ifdef OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION
#define MAX_SUBJECT_NUMBER  20UL
#define MAX_OBSERVER_NUMBER 20UL

template<typename T>
class Observer {
    friend class Subject<T>;

private:
    Subject<T>* subjects[MAX_SUBJECT_NUMBER];
    uint32_t subjectNumber = 0;

    bool AddSubject(Subject<T>* subject);
    bool RemoveSubject(Subject<T>* subject);

public:
    ~Observer();
    virtual void OnNotify(const T& t, enum Event event) = 0;
};

template<typename T>
class Subject {
private:
    Observer<T>* observers[MAX_OBSERVER_NUMBER];
    uint32_t observerNumber = 0;

protected:
    void Notify(const T& t, enum Event event) const;

public:
    ~Subject();
    void AddObserver(Observer<T>* observer);
    void RemoveObserver(Observer<T>* observer);
};

#else

template<typename T>
class Observer {
    friend class Subject<T>;

private:
    Observer<T>* prev = NULL;
    Observer<T>* next = NULL;

public:
    ~Observer();
    virtual void OnNotify(const T& t, enum Event event) = 0;
};

template<typename T>
class Subject {
private:
    Observer<T>* head = NULL;

protected:
    void Notify(const T& t, enum Event event) const;

public:
    ~Subject();
    void AddObserver(Observer<T>* observer);
    void RemoveObserver(Observer<T>* observer);
};

#endif // OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION

#endif // __OBSERVER_H__
