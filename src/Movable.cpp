/*
 *  Movable.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/3/09.
 *
 */

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "Movable.h"

void Movable::setX(const double value) {
    _x = value;
}

void Movable::setY(const double value) {
    _y = value;
}

void Movable::setZ(const double value) {
    _z = value;
}

double Movable::getX() const {
    return _x;
}

double Movable::getY() const {
    return _y;
}

double Movable::getZ() const {
    return _z;
}

void Movable::copyCoordinatesFrom(const Movable& object) {
    _x = object.getX();
    _y = object.getY();
    _z = object.getZ();
}

void Movable::initialize() {
    initialize(0.0, 0.0, 0.0);
}

void Movable::initialize(const double x, const double y, const double z) {
    setX(x);
    setY(y);
    setZ(z);
}

void Movable::doTranslation() const {
    glTranslatef(getX(), getY(), getZ());
}
