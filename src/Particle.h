/*
 *  Particle.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#ifndef NHZ_PARTICLE_H
#define NHZ_PARTICLE_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Renderable.h"
#include "Movable.h"

class ParticleFountain;

class Particle : public Renderable, public Movable {
  public:
    Particle(ParticleFountain* const parent);
    ~Particle();
    void render() const;
    void idle(const int elapsed);
  protected:
    void initialize(ParticleFountain* parent);
    void renderParticle() const;
  private:
    static GLuint _particleID;
    ParticleFountain* _parent;
    float _life;
    float _fade;
    float _r, _g, _b;
    float _xVelocity, _yVelocity, _zVelocity;
};

#include "ParticleFountain.h"

#endif
