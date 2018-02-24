//
// Created by derya on 11.12.2017.
//

#ifndef GTUSETBASE_H
#define GTUSETBASE_H


#include "GTUIterator.h"
#include <iostream>
#include <exception>
#include <utility>        // for pair

namespace CaptainD {


    template<class T>
    class GTUSetBase {
    public:
        friend class GTUIterator<T>;    // GTUIterator class ini friend yaparak eristim
        GTUSetBase() = default;

        virtual bool empty() const = 0;
        virtual int size() const = 0;

    protected:
        virtual int max_size() const = 0;
        virtual void erase(const T &val) = 0;
        virtual void clear() = 0;
        virtual int count(const T &val) const = 0;
        virtual GTUIterator<T> find(const T &val) = 0;
        virtual std::pair<GTUIterator<T>, bool> insert(const T &val) = 0;
        virtual GTUIterator<T> begin()  = 0;
        virtual GTUIterator<T> end()  = 0;

    };

}

#endif //GTUSETBASE_H
