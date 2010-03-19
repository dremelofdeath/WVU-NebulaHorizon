/*
 *  Quadruple.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/21/09.
 *
 */

#include "Triple.h"

#ifndef NHZ_QUADRUPLE_H
#define NHZ_QUADRUPLE_H

template <class T>
class Quadruple : public Triple<T> {
  public:
    Quadruple(T first, T second, T third, T fourth)
    : Triple<T>(first, second, third) {
      initialize(first, second, third, fourth);
    }
    T getFourth() {
      return _fourth;
    }
    virtual T operator[](int i) {
      if(i == 3) {
        return getFourth();
      }
      return Triple<T>::operator[](i);
    }
  protected:
    virtual int getMaxCapacity() const {
      return 4;
    }
    void initialize(T first, T second, T third, T fourth) {
      Triple<T>::initialize(first, second, third);
      _fourth = fourth;
    }
  private:
    T _fourth;
};

#endif
