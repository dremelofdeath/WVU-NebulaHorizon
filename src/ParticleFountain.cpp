/*
 *  ParticleFountain.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#include "ParticleFountain.h"

ParticleFountain::ParticleFountain(int particles) {
  initialize(particles);
}

ParticleFountain::~ParticleFountain() {
  delete _particles;
}

void ParticleFountain::render() const {
  glDisable(GL_LIGHTING);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  //glBindTexture(GL_TEXTURE_2D, _textureID);
  std::vector<Particle>::const_iterator particle_itr = _particles->begin();
  while(particle_itr != _particles->end()) {
    glPushMatrix();
    particle_itr->render();
    glPopMatrix();
    particle_itr++;
  }
}

void ParticleFountain::idle(const int elapsed) {
  std::vector<Particle>::iterator particle_itr = _particles->begin();
  while(particle_itr != _particles->end()) {
    particle_itr->idle(elapsed);
    particle_itr++;
  }
}

void ParticleFountain::setSpeedModifier(float speed) {
  _speedModifier = speed;
}

float ParticleFountain::getSpeedModifier() const {
  return _speedModifier;
}

void ParticleFountain::setXSpeed(float value) {
  _xVelocity = value;
}

void ParticleFountain::setYSpeed(float value) {
  _yVelocity = value;
}

void ParticleFountain::setZSpeed(float value) {
  _zVelocity = value;
}

float ParticleFountain::getXSpeed() const {
  return _xVelocity;
}

float ParticleFountain::getYSpeed() const {
  return _yVelocity;
}

float ParticleFountain::getZSpeed() const {
  return _zVelocity;
}

void ParticleFountain::setXGravity(float value) {
  _xGravity = value;
}

void ParticleFountain::setYGravity(float value) {
  _yGravity = value;
}

void ParticleFountain::setZGravity(float value) {
  _zGravity = value;
}

float ParticleFountain::getXGravity() const {
  return _xGravity;
}

float ParticleFountain::getYGravity() const {
  return _yGravity;
}

float ParticleFountain::getZGravity() const {
  return _zGravity;
}

void ParticleFountain::setRed(float color) {
  _r = color;
}

void ParticleFountain::setGreen(float color) {
  _g = color;
}

void ParticleFountain::setBlue(float color) {
  _b = color;
}

float ParticleFountain::getRed() const {
  return _r;
}

float ParticleFountain::getGreen() const {
  return _g;
}

float ParticleFountain::getBlue() const {
  return _b;
}

void ParticleFountain::initialize(int particles) {
  Movable::initialize(0.0, 0.0, 0.0);
  _speedModifier = 1.0f;
  _r = 1.0f;
  _g = 1.0f;
  _b = 1.0f;
  _xVelocity = 0.0f;
  _yVelocity = 0.0f;
  _zVelocity = 0.0f;
  _xGravity = 0.0f;
  _yGravity = 0.0f;
  _zGravity = 0.3f;
  _nParticles = particles;
  _particles = new std::vector<Particle>(_nParticles, Particle(this));
}
