//
// Created by derya on 11.12.2017.
//

#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include <iostream>
#include <exception>
#include <memory>

namespace CaptainD{

template<class T>
class GTUIterator {
public:
    GTUIterator() = default;

    explicit GTUIterator(T *x);

    ~GTUIterator() = default;

    GTUIterator(const GTUIterator &obj);

    GTUIterator<T> &operator=(const GTUIterator<T> &other);

    GTUIterator &operator++();

    GTUIterator operator++(int);

    GTUIterator &operator--();

    GTUIterator operator--(int);

    bool operator==(const GTUIterator &obj) const;

    bool operator!=(const GTUIterator &obj) const;

    T &operator*();

    T *operator->();

private:
    T *ptr;
};

}
#endif //GTUITERATOR_H
