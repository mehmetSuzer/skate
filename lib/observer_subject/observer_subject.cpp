
#include "observer_subject.h"

#ifdef OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION

//-------------------------------------- OBSERVER --------------------------------------// 

// Called only in subject->addObserver().
// Returns true if the subject is added successfully.
// Otherwise, it returns false.
template<typename T>
bool Observer<T>::AddSubject(Subject<T>* subject) {
    // Check whether the subject is already in the array
    for (uint32_t i = 0; i < subjectNumber; i++) {
        if (subjects[i] == subject) {
            return false;
        }
    }

    // If it is not in the array, add to the end
    if (subjectNumber < maxSubjectNumber) {
        subjects[subjectNumber++] = subject;
        return true;
    }
    return false;
}

// Called only when the subject is deleted, and the subject removes the observer.
// Returns true if the subject is removed successfully.
// Otherwise, it returns false.
template<typename T>
bool Observer<T>::RemoveSubject(Subject<T>* subject) {
    // Linear search on the array
    for (uint32_t i = 0; i < subjectNumber; i++) {
        if (subjects[i] == subject) {
            subjects[i] = subjects[--subjectNumber];
            return true;
        }
    }
    return false;
}

// Removes itself from observer lists of subjects that it observes.
template<typename T>
Observer<T>::~Observer() {
    for (uint32_t i = 0; i < subjectNumber; i++) {
        subjects[i]->RemoveObserver(this);
    }
}

//-------------------------------------- SUBJECT --------------------------------------// 

// Notifies all observers in the array.
template<typename T>
void Subject<T>::Notify(const T& t, enum Event event) const {
    for (uint32_t i = 0; i < observerNumber; i++) {
        observers[i]->OnNotify(t, event);
    }
}

// Removes itself from subject lists of observers that it notifies.
template<typename T>
Subject<T>::~Subject() {
    for (uint32_t i = 0; i < observerNumber; i++) {
        observers[i]->RemoveSubject(this);
    }
}

template<typename T>
void Subject<T>::AddObserver(Observer<T>* observer) {
    // Check whether the observer is already in the array
    for (uint32_t i = 0; i < observerNumber; i++) {
        if (observers[i] == observer) {
            return;
        }
    }

    // If it is not in the array, add to the end
    if (observerNumber < maxObserverNumber && observer->AddSubject(this)) {
        observers[observerNumber++] = observer;
    }
}

template<typename T>
void Subject<T>::RemoveObserver(Observer<T>* observer) {
    // Linear search on the array
    for (uint32_t i = 0; i < observerNumber; i++) {
        if (observers[i] == observer) {
            if (observer->RemoveSubject(this)) {
                observers[i] = observers[--observerNumber];
            }
            return;
        }
    }
}

#else

//-------------------------------------- OBSERVER --------------------------------------// 

// Removes itself from the linked list.
template<typename T>
Observer<T>::~Observer() {
    if (next != NULL) {
        next->prev = prev;
    }
    if (prev != NULL) {
        prev->next = next;
    }
}

// -------------------------------------- SUBJECT --------------------------------------// 

// Removes all observers from the linked list.
template<typename T>
Subject<T>::~Subject() {
    Observer<T>* observer = head;
    while (observer != NULL) {
        head = observer->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        observer->next = NULL;
        observer = head;
    }
}

// Notifies all observers in the linked list.
template<typename T>
void Subject<T>::Notify(const T& t, enum Event event) const {
    Observer<T>* observer = head;
    while (observer != NULL) {
        observer->OnNotify(t, event);
        observer = observer->next;
    }
}

template<typename T>
void Subject<T>::AddObserver(Observer<T>* observer) {
    // Linear search over the linked list
    Observer<T>* current = head;
    while (current != NULL) {
        if (current == observer) { 
            return; 
        }
        current = current->next;
    }

    // If the observer is not in the list, add it to the beginning
    observer->next = head;
    if (observer->next != NULL) {
        observer->next->prev = observer;
    }
    head = observer;
}

template<typename T>
void Subject<T>::RemoveObserver(Observer<T>* observer) {
    // Check if the observer is the head of the list
    if (head == observer) {
        head = observer->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        observer->next = NULL;
        return;
    }

    // Find the observer in the list and remove it
    Observer<T>* current = head;
    while (current != NULL) {
        if (current->next == observer) {
            current->next = observer->next;
            observer->prev = NULL;
            if (observer->next != NULL) {
                observer->next->prev = current;
            }
            observer->next = NULL;
            return;
        }
        current = current->next;
    }
}

#endif // OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION
