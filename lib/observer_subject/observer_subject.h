
#ifndef __OBSERVER_SUBJECT_H__
#define __OBSERVER_SUBJECT_H__

#include <stddef.h>
#include <stdint.h>
#include "config.h"

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

    bool AddSubject(Subject<T>* subject) noexcept;
    bool RemoveSubject(Subject<T>* subject) noexcept;

public:
    ~Observer() noexcept;
    virtual void OnNotify(const T& t, enum Event event) noexcept = 0;
};

template<typename T>
class Subject {
private:
    static const uint32_t maxObserverNumber = 20;
    Observer<T>* observers[maxObserverNumber];
    uint32_t observerNumber = 0;

protected:
    void Notify(const T& t, enum Event event) const noexcept;

public:
    ~Subject() noexcept;
    void AddObserver(Observer<T>* observer) noexcept;
    void RemoveObserver(Observer<T>* observer) noexcept;
};

#else

template<typename T>
class Observer {
    friend class Subject<T>;

private:
    Observer<T>* prev = NULL;
    Observer<T>* next = NULL;

public:
    ~Observer() noexcept;
    virtual void OnNotify(const T& t, enum Event event) noexcept = 0;
};

template<typename T>
class Subject {
private:
    Observer<T>* head = NULL;

protected:
    void Notify(const T& t, enum Event event) const noexcept;

public:
    ~Subject() noexcept;
    void AddObserver(Observer<T>* observer) noexcept;
    void RemoveObserver(Observer<T>* observer) noexcept;
};

#endif // __OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION__

#endif // __OBSERVER_SUBJECT_H__
