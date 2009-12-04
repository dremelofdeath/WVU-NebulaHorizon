/*
 *  Player.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/24/09.
 *
 */

#ifndef NHZ_PLAYER_H
#define NHZ_PLAYER_H

#include "Renderable.h"
#include "Material.h"
#include "Positionable.h"

class Player : public Renderable, public Material, public Positionable {
    public:
        Player();
        Player(float xVelocity, float yVelocity);
        void render() const;
        void idle(int elapsed);
    protected:
        static Renderable& getMesh();
        void initialize();
        void initialize(float xVelocity, float yVelocity);
    private:
        static Renderable* _mesh;
        float _lastX, _lastY;
        float _xVelocity, _yVelocity;
        float _lastXAngle, _lastZAngle;
};

#endif
