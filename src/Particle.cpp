/*
 *  Particle.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Particle.h"

Particle::Particle(ParticleFountain* const parent) {
    initialize(parent);
}

void Particle::render() const {
    glTranslatef(_x, _y, _z);
    glColor4f(_r, _g, _b, _life);
    /*glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(1, 1);
    glVertex3f(_x+0.5f, _y+0.5f, _z);
    glTexCoord2d(0, 1);
    glVertex3f(_x-0.5f, _y+0.5f, _z);
    glTexCoord2d(1, 0);
    glVertex3f(_x+0.5f, _y-0.5f, _z);
    glTexCoord2d(0, 0);
    glVertex3f(_x-0.5f, _y-0.5f, _z);*/
    glutSolidSphere(0.04*(_life+0.2), 9, 9);
    glEnd();
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
}

void Particle::initialize(ParticleFountain* parent) {
    Movable::initialize(rand()%100/500.0-0.1,
                        rand()%100/500.0-0.1,
                        rand()%100/500.0-0.1);
    _parent = parent;
    _life = 1.0f;
    _fade = (float)((rand()%100)/30.5f+0.853f);
    _r = _parent->getRed();
    _g = _parent->getGreen();
    _b = _parent->getBlue();
    _xVelocity = _parent->getXSpeed()+(float)((rand()%60)-30.0f)/155;
    _yVelocity = _parent->getYSpeed()+(float)((rand()%60)-30.0f)/155;
    _zVelocity = _parent->getZSpeed()+(float)((rand()%60)-0.0f)/32;
}

