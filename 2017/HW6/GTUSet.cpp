//
// Created by derya on 11.12.2017.
//

#include "GTUSet.h"


using namespace std;

namespace CaptainD {


    template<class T>
    GTUSet<T>::GTUSet(int size) {
        _setPtr = shared_ptr<T>(new T[size], default_delete<T[]>());
        _sizePtr = size;
    }


    template<class T>
    shared_ptr<GTUSet<T>> GTUSet<T>::getShrd_ptr() {
        return _setPtr;
    }

    template<class T>
    bool GTUSet<T>::empty() const {
        if (_sizePtr == 0);
    }

    template<class T>
    int GTUSet<T>::size() const {
        return _sizePtr;
    }

    template<class T>
    // kullanilmadigi icin direk shared_ptr in size ini return ettim
    int GTUSet<T>::max_size() const {
        return _sizePtr;
    }

    template<class T>
    void GTUSet<T>::erase(const T &val) {
        int position = 0;
        // silinecek value array de hangi konumda oldugu bulunur
        for (int k = 0; k < _sizePtr; ++k) {
            if (_setPtr.get()[k] == val)
                position = k;
        }

        GTUSet<T> temp(_sizePtr);
        temp._setPtr = _setPtr;

        clear();

        // value nun konumuna kadar elementleri temp e atar
        int i, j;
        for (i = 0; i < position; ++i)
            insert(temp._setPtr.get()[i]);

        // value nun bulundugu konumu atlayarak temp e atmaya devam eder
        for (j = i + 1; j < temp._sizePtr; ++j)
            insert(temp._setPtr.get()[j]);

        // size i azalt
        _sizePtr = temp._sizePtr - 1;

        temp._setPtr = nullptr;
        temp._sizePtr = 0;
    }

    template<class T>
    void GTUSet<T>::clear() {
        _setPtr.reset(new T);      // shared_ptr i delete eder
        _setPtr = nullptr;
        _sizePtr = 0;
    }

    template<class T>
    int GTUSet<T>::count(const T &val) const {
        for (int i = 0; i < _sizePtr; ++i) {
            if (_setPtr.get()[i] == val)
                return 1;
        }
        return 0;
    }


    template<class T>
    GTUIterator<T> GTUSet<T>::find(const T &val) {
        // iteratorla array icinde dolasip value var mi diye bakar
        for (GTUIterator<T> it = this->begin(); it != this->end(); ++it) {
            if (*it == val)
                return it;
        }
        return this->end();
    }


    template<class T>
    void GTUSet<T>::printArr() const {
        for (int i = 0; i < _sizePtr; ++i) {
            cout << i << "-> " << _setPtr.get()[i] << endl;
        }
    }

    template<class T>
    pair<GTUIterator<T>, bool> GTUSet<T>::insert(const T &val) {   //pair<iterator,bool> insert (const value_type& val);
        pair<GTUIterator<T>, bool> temp;

        for (int j = 0; j < _sizePtr; ++j) {
            if (_setPtr.get()[j] == val) {
                temp.second = false;
                temp.first = find(val);
                throw 1;
            }
        }

        // yeni eleman icin kendi size indan +1 fazla yer allocate eder
        GTUSet<T> tempS(_sizePtr + 1);

        // shared_ptr icindekileri temp degiskene atar
        for (int i = 0; i < _sizePtr; ++i)
            tempS._setPtr.get()[i] = _setPtr.get()[i];

        // eklenecek degeri son elemente atar
        tempS._setPtr.get()[_sizePtr] = val;

        // temp in shared_ptr ini this in shared_ptr ina atamak icin resetler
        _setPtr.reset(new T);

        this->_setPtr = tempS._setPtr;
        this->_sizePtr = tempS._sizePtr;

        return temp;
    }


    template<class T>
    // shared_ptr in ilk elemanini iterator pointerina assign eden constructor a yollar
    GTUIterator<T> GTUSet<T>::begin() {
        return GTUIterator<T>(&_setPtr.get()[0]);
    }

    template<class T>
    GTUIterator<T> GTUSet<T>::end() {
        return GTUIterator<T>(&_setPtr.get()[0] + _sizePtr);
    }



}


