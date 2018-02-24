/*
In this homework, you will write a templated class hierarchy for sets and maps.
The class GTUSetBase is an abstract class with the following pure virtual member functions.
empty - > Test whether container is empty
size - > Return container size
max_size - > Return maximum size
insert -> Insert element, throws exception std::bad_pafram if the element is already in the set
erase - > Erase element
clear -> Clear all content
find - > Get iterator to element
count - > Count elements with a specific value
begin - > Return iterator to beginning
end - > Return iterator to end
The class GTUSet<T> derives from the base class and implements all of the functions appropriately.
It will keep its data using dynamic memory techniques with shared_ptr STL pointers. Do not use
regular pointers or STL container classes.The class GTUMap<K, V> derives from GTUSet<std::pair<K, V> > and implements the following
extra function
operator[]
Access element
V& operator[] (const K& k);
If k matches the key of an element in the set, the function returns a reference to its mapped value.
The class GTUIterator implements iterator operators such as *, ->, ++, --, =, and ==.
You will also write the following global function
template <class T>
std::shared_ptr<GTUSetBase<T> > setIntersection<T> (const GTUSetBase<T>&, const GTUSetBase<T>&);
The returned set is the intersection of the two sets.
Write your driver program to test the all the classes and all of their functions. Do not forget to test the
global function with sets and maps.
*/
//
// Created by derya on 11.12.2017.
//

#include "GTUIterator.h"


namespace CaptainD {


    template<class T>
    GTUIterator<T>::GTUIterator(T *x) : ptr(x) {
        /* Intentionally empty */
    }

    template<class T>
    GTUIterator<T>::GTUIterator(const GTUIterator<T> &obj) : ptr(obj.ptr) {
        /* Intentionally empty */
    }

    template<class T>
    GTUIterator<T> &GTUIterator<T>::operator++() {
        ++ptr;
        return *this;
    }

    template<class T>
    GTUIterator<T> GTUIterator<T>::operator++(int) {
        GTUIterator<T> tmp(*this);
        operator++();
        return tmp;
    }

    template<class T>
    bool GTUIterator<T>::operator==(const GTUIterator<T> &obj) const {
        return ptr == obj.ptr;
    }

    template<class T>
    T &GTUIterator<T>::operator*() {
        return *ptr;
    }

    template<class T>
    GTUIterator<T> &GTUIterator<T>::operator=(const GTUIterator<T> &other) {
        if (ptr != other.ptr) {
            delete ptr;
            ptr = nullptr;
            ptr = other.ptr;
        }
        return *this;
    }

    template<class T>
    T *GTUIterator<T>::operator->() {
        return ptr;
    }

    template<class T>
    bool GTUIterator<T>::operator!=(const GTUIterator<T> &obj) const {
        return (!(*this == obj));
    }

    template<class T>
    GTUIterator<T> GTUIterator<T>::operator--(int) {
        GTUIterator<T> tmp(*this);
        operator--();
        return tmp;
    }

    template<class T>
    GTUIterator<T> &GTUIterator<T>::operator--() {
        --ptr;
        return *this;
    }

}
