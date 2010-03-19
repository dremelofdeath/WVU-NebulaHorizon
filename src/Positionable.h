/*
 *  Positionable.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#ifndef NHZ_POSITIONABLE_H
#define NHZ_POSITIONABLE_H

#include "Movable.h"
#include "Rotatable.h"

class Positionable : public Movable, public Rotatable {
  public:
    void lookAt(const Movable& target);
  protected:
    void initialize();
    double calculateLookAngle(double i, double ti, double j, double tj);
};

#endif
