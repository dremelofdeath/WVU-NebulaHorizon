/*
 *  Player.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/24/09.
 *  Copyright 2009 West Virginia University. All rights reserved.
 *
 */

#ifndef NHZ_PLAYER_H
#define NHZ_PLAYER_H

#include "Renderable.h"

class Player : public Renderable {
    public:
        Player();
        Player(float xVelocity, float yVelocity);
        void render();
        void idle(int elapsed);
        void setAmbientMaterial(const float (&material)[4]);
        void setDiffuseMaterial(const float (&material)[4]);
        void setSpecularMaterial(const float (&material)[4]);
    protected:
        static Renderable& getMesh();
        void initialize();
        void initialize(float xVelocity, float yVelocity);
    private:
        static Renderable* _mesh;
        float _x, _y;
        float _lastX, _lastY;
        float _xVelocity, _yVelocity;
        float _xAngle, _zAngle;
        float _lastXAngle, _lastZAngle;
        float _ambient[4], _diffuse[4], _specular[4];
};

#endif
