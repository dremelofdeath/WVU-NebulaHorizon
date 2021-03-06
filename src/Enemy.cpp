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
#include "nhz_common.h"

Renderable* Enemy::_mesh = 0;

Enemy::Enemy() {
  initialize();
}

Enemy::Enemy(Movable* const target) {
  initialize(target);
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

void Enemy::idle(const int elapsed) {
  float time = (float)elapsed;
  _x += _xVelocity*time/1000.0f;
  _y += _yVelocity*time/1000.0f;
  _z += _zVelocity*time/1000.0f;
  _xVelocity -= (float)(_x/9.0f*time/1000.0f);
  _yVelocity -= (float)(_y/40.0f*time/1000.0f);
  if(_target != 0 ) {
    lookAt(*_target);
  }
}

void Enemy::setTarget(Movable* const target) {
  _target = target;
}

Renderable& Enemy::getMesh() {
  if(_mesh == 0) {
    std::ifstream drone_file(NHZ_RES_T("meshes", "drone.obj"));
    MeshLoader* loader = new WavefrontGLMeshLoader;
    _mesh = loader->loadMesh(drone_file);
    delete loader;
    drone_file.close();
  }
  return *_mesh;
}

void Enemy::initialize() {
  static const float ambient[4] = {0.3f, 0.5f, 0.3f, 1.0f};
  static const float diffuse[4] = {0.62f, 0.9f, 0.62f, 1.0f};
  static const float specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  Material::initialize();
  Positionable::initialize();
  Movable::initialize(-16.0, 9.0, -150.0);
  setAmbientMaterial(ambient);
  setDiffuseMaterial(diffuse);
  setSpecularMaterial(specular);
  setShininess(27.8f);
  _target = 0;
  _xVelocity = 7.0;
  _yVelocity = 0.0;
  _zVelocity = 12.0;
}

void Enemy::initialize(Movable* const target) {
  initialize();
  setTarget(target);
}
