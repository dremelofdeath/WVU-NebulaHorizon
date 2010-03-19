/*
 *  EnemySpawner.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#ifndef NHZ_ENEMYSPAWNER_H
#define NHZ_ENEMYSPAWNER_H

#include "ProcessorEntity.h"
#include "Movable.h"
#include "Enemy.h"

class EnemySpawner : public ProcessorEntity {
  public:
    EnemySpawner(Movable* const target);
    EnemySpawner(Movable* const target, const int period);
    void idle(const int elapsed);
    void setPeriod(const int period);
    void setTarget(Movable* const target);
  protected:
    void initialize(Movable* const target);
    void initialize(Movable* const target, const int period);
    void spawnEnemy();
  private:
    Movable* _target;
    int _period;
    int _counter;
};

#endif
