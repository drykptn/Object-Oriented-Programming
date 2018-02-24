//
// Created by derya on 11.12.2017.
//

#ifndef GTUSET_H
#define GTUSET_H

#include <memory>
#include "GTUSetBase.h"

namespace CaptainD {
    template<class T>
    class GTUSet : public GTUSetBase<T> {
    public:
        GTUSet() = default;
        explicit GTUSet(int size);
        void printArr() const;                 // shared_ptr array ini print eder
        std::shared_ptr<GTUSet<T> > getShrd_ptr();

        bool empty() const override;
        int size() const override;                                    // size_type
        int max_size() const override;                                // size_type
        void erase(const T &val) override;
        void clear() override;
        int count(const T &val) const override;
        GTUIterator<T> find(const T &val) override;                       // value_type
        std::pair<GTUIterator<T>, bool> insert(const T &val) override;          // value_type
        GTUIterator<T> begin() override;
        GTUIterator<T> end() override;

    protected:
        std::shared_ptr<T> _setPtr;
        int _sizePtr = 0;         // int
    };

}

#endif //GTUSET_H
