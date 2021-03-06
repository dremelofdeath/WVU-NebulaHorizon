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
#include "TextFileReader.h"
#include "Player.h"

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
  glDeleteProgram(_shaderProgram);
  glDeleteShader(_fragmentShader);
  glDeleteShader(_vertexShader);
}

void Player::render() const {
  GLint refraction;
  GLint slopes;
  Renderable::render();
  glPushMatrix();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glDisable(GL_TEXTURE_2D);
  glUseProgram(_shaderProgram);
  refraction = glGetUniformLocation(_shaderProgram, "refraction");
  slopes = glGetUniformLocation(_shaderProgram, "slopes");
  glUniform1f(refraction, 40.0f);
  glUniform1f(slopes, 0.30f);
  useMaterial();
  doTranslation();
  glRotatef((GLfloat)_xAngle, 1.0f, 0.0f, 0.0f);
  glRotatef((GLfloat)_zAngle, 0.0f, 0.0f, 1.0f);
  glPushMatrix();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glTranslatef(0.0f, 0.0f, _fountainDistance);
  //_fountain->render();
  glPopAttrib();
  glPopMatrix();
  glScaled(0.35, 0.35, 0.35);
  getMesh().render();
  glUseProgram(0);
  glPopMatrix();
}

void Player::idle(const int elapsed) {
  float time = (float)elapsed;
  //_fountain->setX(getX());
  //_fountain->setY(getY());
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
  /*static const float ambient[4] = {0.4f, 0.4f, 0.45f, 1.0f};
  static const float diffuse[4] = {0.8f, 0.8f, 1.0f, 1.0f};
  static const float specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};*/
  static const float ambient[4] = {0.25f, 0.25f, 0.25f, 1.0f};
  static const float diffuse[4] = {0.4f, 0.4f, 0.4f, 1.0f};
  static const float specular[4] = {0.774597, 0.774597, 0.774597, 1.0};
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
  setShininess(76.8);
  //setShininess(27.8f);

  _fountain = new ParticleFountain(750);
  /* a pretty awesome red flame
  _fountain->setRed(1.0f);
  _fountain->setGreen(0.2f);
  _fountain->setBlue(0.01f);
  */
  _fountain->setRed(0.04f);
  _fountain->setGreen(0.4f);
  _fountain->setBlue(1.0f);

  // load shaders
  _vertexShader = glCreateShader(GL_VERTEX_SHADER);
  _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  TextFileReader vertexFile(NHZ_RES_T("shaders", "v_cook_torrance.glsl"));
  TextFileReader fragmentFile(NHZ_RES_T("shaders", "f_cook_torrance.glsl"));
  const GLchar* vShaderCode = (const GLchar*)vertexFile.getFileContents();
  glShaderSource(_vertexShader, 1, &vShaderCode, NULL);
  glCompileShader(_vertexShader);
  const GLchar* fShaderCode = (const GLchar*)fragmentFile.getFileContents();
  glShaderSource(_fragmentShader, 1, &fShaderCode, NULL);
  glCompileShader(_fragmentShader);

  // link program
  _shaderProgram = glCreateProgram();
  glAttachShader(_shaderProgram, _vertexShader);
  glAttachShader(_shaderProgram, _fragmentShader);
  glLinkProgram(_shaderProgram);
}
