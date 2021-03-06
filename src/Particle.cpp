/*
 *  Particle.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#include "Particle.h"

#include <cmath>

#ifdef __APPLE__
#include <OpenGL/glext.h>
#else
#include <GL/glext.h>
#endif

#include "nhz_common.h"

GLuint Particle::_particleID = 0;

Particle::Particle(ParticleFountain* const parent) {
  initialize(parent);
}

Particle::~Particle() {
  if(_particleID != 0) {
    glDeleteLists(_particleID, 1);
  }
}

void Particle::render() const {
  float scaleFactor = 0.04f*(_life+0.2f);
  glColor4f(_r, _g, _b, _life);
  doTranslation();
  glScalef(scaleFactor, scaleFactor, scaleFactor);
  glPointSize(8.0f*_life);
  renderParticle();
}

void Particle::idle(const int elapsed) {
  float time = (float)elapsed/1000.0f;
  _x += _xVelocity*_parent->getSpeedModifier()*time;
  _y += _yVelocity*_parent->getSpeedModifier()*time;
  _z += _zVelocity*_parent->getSpeedModifier()*time;
  _xVelocity += _parent->getXGravity()*time;
  _yVelocity += _parent->getYGravity()*time;
  _zVelocity += _parent->getZGravity()*time;
  _life -= _fade*time;
  if(_life < 0.0f) {
    initialize(_parent);
  }
  if(_particleID == 0) {
    _particleID = glGenLists(1);
    glNewList(_particleID, GL_COMPILE);
    //glutSolidSphere(1.0, 8, 8);
    glBegin(GL_POINTS);
    glVertex3i(0, 0, 0);
    glEnd();
    glEndList();
  }
}

void Particle::renderParticle() const {
  if(_particleID != 0) {
    glCallList(_particleID);
  }
}

void Particle::initialize(ParticleFountain* parent) {
  double xmod = rand()%100/500.0-0.1;
  double angle = std::acos(10.0*xmod);
  Movable::initialize(parent->getX()+xmod,
      //parent->getY()+rand()%100/500.0-0.1,
      parent->getY()+(rand()%100/500.0-0.1)*std::sin(angle),
      parent->getZ()+rand()%100/500.0-0.1);
  _parent = parent;
  _life = 1.0f;
  _fade = (float)((rand()%100)/30.5f+0.853f);
  _r = _parent->getRed();
  _g = _parent->getGreen();
  _b = _parent->getBlue();
  _xVelocity = _parent->getXSpeed()+(float)((rand()%60)-30.0f)/155;
  _yVelocity = _parent->getYSpeed()+(float)((rand()%60)-30.0f)/155;
  //_zVelocity = _parent->getZSpeed()+(float)((rand()%60)-0.0f)/32;
  _zVelocity = _parent->getZSpeed()+(float)((rand()%60)-0.0f)/25;
}

