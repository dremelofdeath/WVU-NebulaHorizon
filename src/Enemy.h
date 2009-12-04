/*
 *  Enemy.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/3/09.
 *
 */

#ifndef NHZ_ENEMY_H
#define NHZ_ENEMY_H

#include "Renderable.h"
#include "Material.h"
#include "Positionable.h"

class Enemy : public Renderable, public Material, public Positionable {
    public:
        Enemy();
        void render() const;
        void idle(int elapsed);
        void setTarget(Movable* const target);
    protected:
        static Renderable& getMesh();
        void initialize();
    private:
        static Renderable* _mesh;
        float _xVelocity, _yVelocity;
        Movable* _target;
};

#endif
