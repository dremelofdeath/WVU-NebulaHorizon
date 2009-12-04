/*
 *  EnemySpawner.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/4/09.
 *
 */

#include "EnemySpawner.h"
#include "RenderQueue.h"

EnemySpawner::EnemySpawner(Movable* const target) {
    initialize(target);
}

EnemySpawner::EnemySpawner(Movable* const target, const int period) {
    initialize(target, period);
}

void EnemySpawner::idle(int elapsed) {
    _counter += elapsed;
    if(_counter >= _period) {
        spawnEnemy();
        _counter -= _period;
    }
}

void EnemySpawner::setPeriod(const int period) {
    _period = period;
}

void EnemySpawner::setTarget(Movable* const target) {
    _target = target;
}

void EnemySpawner::initialize(Movable* const target) {
    initialize(target, 2500);
}

void EnemySpawner::initialize(Movable* const target, const int period) {
    setTarget(target);
    setPeriod(period);
    _counter = 0;
}

void EnemySpawner::spawnEnemy() {
    Enemy* enemy = new Enemy(_target);
    RenderQueue::getInstance()->enqueue(*enemy);
    RenderQueue::getInstance()->postQueueClobbered();
}
