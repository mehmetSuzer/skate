
#ifndef __OBSERVER_SUBJECT_H__
#define __OBSERVER_SUBJECT_H__

#include <config.h>
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

#ifdef __OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION__

template<typename T>
class Observer {
    friend class Subject<T>;

private:
    static const uint32_t maxSubjectNumber = 20;
    Subject<T>* subjects[maxSubjectNumber];
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
    static const uint32_t maxObserverNumber = 20;
    Observer<T>* observers[maxObserverNumber];
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

#endif // __OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION__

#endif // __OBSERVER_SUBJECT_H__
