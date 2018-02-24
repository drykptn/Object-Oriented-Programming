//
// Created by derya on 11.12.2017.
//

#include "GTUMap.h"

namespace CaptainD {

    template<class T, class K>
    K &GTUMap<T, K>::operator[](const T &t) {
        for (int i = 0; i < this->_sizePtr; ++i) {
            if (t == (this->_setPtr).get()[i].first)
                return (this->_setPtr).get()[i].second;
        }
        throw 2;
    }
}