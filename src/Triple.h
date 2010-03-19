/*
 *  Triple.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/21/09.
 *
 */

#include "Tuple.h"

#ifndef NHZ_TRIPLE_H
#define NHZ_TRIPLE_H

template <class T>
class Triple : public Tuple<T> {
  public:
    Triple(T first, T second, T third)
    : Tuple<T>(first, second) {
      initialize(first, second, third);
    }
    T getThird() {
      return _third;
    }
    virtual T operator[](const int i) {
      if(i == 2) {
        return getThird();
      }
      return Tuple<T>::operator[](i);
    }
  protected:
    virtual int getMaxCapacity() const {
      return 3;
    }
    void initialize(T first, T second, T third) {
      Tuple<T>::initialize(first, second);
      _third = third;
    }
  private:
    T _third;
};

#endif
