/*
 *  Enemy.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/3/09.
 *
 */

#include <fstream>
#include "Enemy.h"
#include "WavefrontGLMeshLoader.h"

Renderable* Enemy::_mesh = 0;

Enemy::Enemy() {
    initialize();
}

void Enemy::render() const {
    Renderable::render();
    useMaterial();
    doTranslation();
    doRotation();
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glScaled(0.4, 0.4, 0.4);
    getMesh().render();
}

void Enemy::idle(int elapsed) {
    // nothing at the moment
    if(_target != 0 ) {
        lookAt(*_target);
    }
}

void Enemy::setTarget(Movable* const target) {
    _target = target;
}

Renderable& Enemy::getMesh() {
    if(_mesh == 0) {
        std::ifstream drone_file("drone.obj");
        MeshLoader* loader = new WavefrontGLMeshLoader;
        _mesh = loader->loadMesh(drone_file);
        delete loader;
    }
    return *_mesh;
}

void Enemy::initialize() {
    static const float ambient[4] = {0.3, 0.5, 0.3, 1.0};
    static const float diffuse[4] = {0.62, 0.9, 0.62, 1.0};
    static const float specular[4] = {1.0, 1.0, 1.0, 1.0};
    Material::initialize();
    Positionable::initialize();
    Movable::initialize(0.0, 0.0, -20.0);
    setAmbientMaterial(ambient);
    setDiffuseMaterial(diffuse);
    setSpecularMaterial(specular);
    setShininess(27.8f);
    _target = 0;
}
