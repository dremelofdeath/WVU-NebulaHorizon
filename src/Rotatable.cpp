/*
 *  Rotatable.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "Rotatable.h"

void Rotatable::setXAngle(const double value) {
  _xAngle = value;
}

void Rotatable::setYAngle(const double value) {
  _yAngle = value;
}

void Rotatable::setZAngle(const double value) {
  _zAngle = value;
}

double Rotatable::getXAngle() const {
  return _xAngle;
}

double Rotatable::getYAngle() const {
  return _yAngle;
}

double Rotatable::getZAngle() const {
  return _zAngle;
}

void Rotatable::copyRotationFrom(const Rotatable& object) {
  setXAngle(object.getXAngle());
  setYAngle(object.getYAngle());
  setZAngle(object.getZAngle());
}

void Rotatable::initialize() {
  initialize(0.0, 0.0, 0.0);
}

void Rotatable::initialize(const double x, const double y, const double z) {
  setXAngle(x);
  setYAngle(y);
  setZAngle(z);
}

void Rotatable::doRotation() const {
  glRotatef(_xAngle, 1.0, 0.0, 0.0);
  glRotatef(_yAngle, 0.0, 1.0, 0.0);
  glRotatef(_zAngle, 0.0, 0.0, 1.0);
}
