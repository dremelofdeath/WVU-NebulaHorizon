/*
 *  Player.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/24/09.
 *  Copyright 2009 West Virginia University. All rights reserved.
 *
 */

#include <fstream>
#include "WavefrontGLMeshLoader.h"
#include "KeyboardManager.h"
#include "Player.h"

Renderable* Player::_mesh = 0;

Player::Player() {
    initialize();
}

Player::Player(float xVelocity, float yVelocity) {
    initialize(xVelocity, yVelocity);
}

void Player::render() {
    glTranslatef(_x, _y, -10.0f);
    glScaled(0.25, 0.25, 0.25);
    glRotated(-15.0, 1.0, 0.0, 0.0);
    getMesh().render();
}

void Player::idle(int elapsed) {
    float time = (float)elapsed;
    KeyboardManager& keyboard = KeyboardManager::getInstance();
    if(keyboard.isKeyDown('w')) {
        _y += _yVelocity*time/1000;
    }
    if(keyboard.isKeyDown('a')) {
        _x -= _xVelocity*time/1000;
    }
    if(keyboard.isKeyDown('s')) {
        _y -= _yVelocity*time/1000;
    }
    if(keyboard.isKeyDown('d')) {
        _x += _xVelocity*time/1000;
    }
}

Renderable& Player::getMesh() {
    if(_mesh == 0) {
        std::ifstream viper_file("viper.obj");
        MeshLoader* loader = new WavefrontGLMeshLoader;
        _mesh = loader->loadMesh(viper_file);
        delete loader;
    }
    return *_mesh;
}

void Player::initialize() {
    initialize(1.0f, 1.0f);
}

void Player::initialize(float xVelocity, float yVelocity) {
    _x = 0.0f;
    _y = 0.0f;
    _xVelocity = xVelocity;
    _yVelocity = yVelocity;
}
