/*
 *  Positionable.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <cstdlib>
#include <cmath>

#include "Positionable.h"

void Positionable::lookAt(const Movable& target) {
    setXAngle(-calculateLookAngle(getY(), target.getY(), getZ(), target.getZ()));
    setXAngle(getXAngle()-180.0);
    setYAngle(calculateLookAngle(getX(), target.getX(), getZ(), target.getZ()));
    setYAngle(getYAngle()-180.0);
}

void Positionable::initialize() {
    Movable::initialize();
    Rotatable::initialize();
}

double
Positionable::calculateLookAngle(double i, double ti, double j, double tj) {
    return atan2((i-ti), (j-tj))*180.0/3.14159265;
}
            
