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
    Enemy(Movable* const target);
    void render() const;
    void idle(const int elapsed);
    void setTarget(Movable* const target);
  protected:
    static Renderable& getMesh();
    void initialize();
    void initialize(Movable* const target);
  private:
    static Renderable* _mesh;
    float _xVelocity, _yVelocity, _zVelocity;
    Movable* _target;
};

#endif
