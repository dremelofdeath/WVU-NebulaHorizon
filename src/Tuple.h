/*
 *  Tuple.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/21/09.
 *
 */

#include <stdexcept>

#ifndef NHZ_TUPLE_H
#define NHZ_TUPLE_H

template <class T>
class Tuple {
    public:
        Tuple(T first, T second) {
            initialize(first, second);
        }
        T getFirst() {
            return _first;
        }
        T getSecond() {
            return _second;
        }
        virtual T operator[](const int i) {
            T value;
            checkIndexBounds(i);
            switch(i) {
                case 0:
                    value = getFirst();
                    break;
                case 1:
                    value = getSecond();
                    break;
            }
            return value;
        }
    protected:
        void initialize(T first, T second) {
            _first = first;
            _second = second;
        }
        virtual int getMaxCapacity() const {
            return 2;
        }
        void checkIndexBounds(const int i) const {
            checkIndexBounds(i, getMaxCapacity());
        }
        void checkIndexBounds(const int i, const int max) const {
            if(i < 0 || i >= max) {
                throw std::out_of_range("i");
            }
        }
    private:
        T _first;
        T _second;
};

#endif
