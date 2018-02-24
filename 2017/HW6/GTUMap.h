//
// Created by derya on 11.12.2017.
//

#ifndef GTUMAP_H
#define GTUMAP_H

#include "GTUSet.h"

namespace CaptainD {

    template<class T, class K>
    class GTUMap : public GTUSet<std::pair<T, K> > {
    public:
        GTUMap() = default;
        K &operator[](const T &t);
    };

}
#endif //GTUMAP_H
