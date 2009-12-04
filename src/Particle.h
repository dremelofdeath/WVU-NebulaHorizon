/*
 *  Particle.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#ifndef NHZ_PARTICLE_H
#define NHZ_PARTICLE_H

#include "Renderable.h"
#include "Movable.h"

class ParticleFountain;

class Particle : public Renderable, public Movable {
    public:
        Particle(ParticleFountain* const parent);
        void render() const;
        void idle(const int elapsed);
    protected:
        void initialize(ParticleFountain* parent);
    private:
        ParticleFountain* _parent;
        float _life;
        float _fade;
        float _r, _g, _b;
        float _xVelocity, _yVelocity, _zVelocity;
};

#include "ParticleFountain.h"

#endif
