/*
 *  ParticleFountain.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#ifndef NHZ_PARTICLEFOUNTAIN_H
#define NHZ_PARTICLEFOUNTAIN_H

#include <vector>

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "RenderQueue.h"
#include "Movable.h"

class Particle;

class ParticleFountain : public Renderable, public Movable {
    public:
        ParticleFountain(int particles);
        ~ParticleFountain();
        void render() const;
        void idle(const int elapsed);
        void setSpeedModifier(float speed);
        float getSpeedModifier() const;
        void setXSpeed(float value);
        void setYSpeed(float value);
        void setZSpeed(float value);
        float getXSpeed() const;
        float getYSpeed() const;
        float getZSpeed() const;
        void setXGravity(float value);
        void setYGravity(float value);
        void setZGravity(float value);
        float getXGravity() const;
        float getYGravity() const;
        float getZGravity() const;
        void setRed(float color);
        void setGreen(float color);
        void setBlue(float color);
        float getRed() const;
        float getGreen() const;
        float getBlue() const;
    protected:
        void initialize(int particles);
    private:
        int _nParticles;
        std::vector<Particle>* _particles;
        float _speedModifier;
        float _r, _g, _b;
        float _xVelocity, _yVelocity, _zVelocity;
        float _xGravity, _yGravity, _zGravity;
};

#include "Particle.h"

#endif
