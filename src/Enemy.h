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
#include "Movable.h"

class Enemy : public Renderable, public Material, public Movable {
    public:
        Enemy();
        void render() const;
        void idle(int elapsed);
    protected:
        static Renderable& getMesh();
        void initialize();
    private:
        static Renderable* _mesh;
        float _xVelocity, _yVelocity;
        float _xAngle, _yAngle, _zAngle;
};

#endif
