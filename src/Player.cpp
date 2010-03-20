/*
 *  Player.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/24/09.
 *
 */

#include <iostream>
#include <fstream>
#include "WavefrontGLMeshLoader.h"
#include "KeyboardManager.h"
#include "Player.h"
#include "nhz_common.h"

// TODO: I don't think this should not be here
#include "AudioManager.h"

Renderable* Player::_mesh = 0;

Player::Player() {
  initialize();
}

Player::Player(float xVelocity, float yVelocity) {
  initialize(xVelocity, yVelocity);
}

Player::~Player() {
  delete _fountain;
}

void Player::render() const {
  Renderable::render();
  glPushMatrix();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  _fountain->render();
  glPopAttrib();
  glPopMatrix();
  useMaterial();
  doTranslation();
  glRotatef((GLfloat)_xAngle, 1.0f, 0.0f, 0.0f);
  glRotatef((GLfloat)_zAngle, 0.0f, 0.0f, 1.0f);
  glScaled(0.35, 0.35, 0.35);
  getMesh().render();
}

void Player::idle(const int elapsed) {
  float time = (float)elapsed;
  _fountain->setX(getX());
  _fountain->setY(getY());
  _fountain->setZ(getZ()+_fountainDistance);
  _fountain->idle(elapsed);
  if(elapsed != 0) {
    _lastX = _x;
    _lastY = _y;
    _lastXAngle = _xAngle;
    _lastZAngle = _zAngle;
    KeyboardManager& keyboard = KeyboardManager::getInstance();
    if(keyboard.isKeyDown('w') && !keyboard.isKeyDown('s')) {
      _y += _yVelocity*time/1000;
      _xAngle += _xAngle < 30.0 ? 0.35*time: 0.0;
      if(_xAngle > 30.0) {
        _xAngle = 30.0;
      }
    }
    if(keyboard.isKeyDown('a') && !keyboard.isKeyDown('d')) {
      _x -= _xVelocity*time/1000;
      _zAngle += _zAngle < 45.0 ? 1.0*time: 0.0;
      if(_zAngle > 45.0) {
        _zAngle = 45.0;
      }
    }
    if(keyboard.isKeyDown('s') && !keyboard.isKeyDown('w')) {
      _y -= _yVelocity*time/1000;
      _xAngle -= _xAngle > -30.0 ? 0.35*time: 0.0;
      if(_xAngle < -30.0) {
        _xAngle = -30.0;
      }
    }
    if(keyboard.isKeyDown('d') && !keyboard.isKeyDown('a')) {
      _x += _xVelocity*time/1000;
      _zAngle -= _zAngle > -45.0 ? 1.0*time: 0.0;
      if(_zAngle < -45.0) {
        _zAngle = -45.0;
      }
    }
    if(!keyboard.isKeyDown('a') && !keyboard.isKeyDown('d') ||
        (keyboard.isKeyDown('a') && keyboard.isKeyDown('d'))) {
      if(_zAngle != 0.0) {
        _zAngle += (_zAngle > 0 ? -0.9 : 0.9)*time;
      }
      if((_lastZAngle < 0.0 && _zAngle > 0.0) ||
          (_lastZAngle > 0.0 && _zAngle < 0.0)) {
        _zAngle = 0.0;
      }
    }
    if(!keyboard.isKeyDown('w') && !keyboard.isKeyDown('s') ||
        (keyboard.isKeyDown('w') && keyboard.isKeyDown('s'))) {
      if(_xAngle != 0.0) {
        _xAngle += (_xAngle > 0 ? -0.4 : 0.4)*time;
      }
      if((_lastXAngle < 0.0 && _xAngle > 0.0) ||
          (_lastXAngle > 0.0 && _xAngle < 0.0)) {
        _xAngle = 0.0;
      }
    }
  }
}

// TODO: sound should definitely be put somewhere else
void Player::handleMouseEvent(int button, int state, int x, int y) {
  if(state == 0) {
    AudioManager::getInstance()->playSFX("raygun.wav");
  }
}

Renderable& Player::getMesh() {
  if(_mesh == 0) {
    std::ifstream viper_file(NHZ_RES_T("meshes", "viper.obj"));
    MeshLoader* loader = new WavefrontGLMeshLoader;
    _mesh = loader->loadMesh(viper_file);
    delete loader;
    viper_file.close();
  }
  return *_mesh;
}

void Player::initialize() {
  initialize(1.0f, 1.0f);
}

void Player::initialize(float xVelocity, float yVelocity) {
  static const float ambient[4] = {0.4f, 0.4f, 0.45f, 1.0f};
  static const float diffuse[4] = {0.8f, 0.8f, 1.0f, 1.0f};
  static const float specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  Material::initialize();
  Movable::initialize(0.0, 0.0, -10.0);
  _lastX = 0.0f;
  _lastY = 0.0f;
  _xVelocity = xVelocity;
  _yVelocity = yVelocity;
  _xAngle = 0.0;
  _zAngle = 0.0;
  _lastXAngle = 0.0;
  _lastZAngle = 0.0;
  _fountainDistance = 0.11;//2.05;
  setAmbientMaterial(ambient);
  setDiffuseMaterial(diffuse);
  setSpecularMaterial(specular);
  setShininess(27.8f);
  _fountain = new ParticleFountain(750);
}
