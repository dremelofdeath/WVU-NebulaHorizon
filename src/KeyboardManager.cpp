/*
 *  KeyboardManager.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/24/09.
 *  Copyright 2009 West Virginia University. All rights reserved.
 *
 */

#include <cctype>
#include "KeyboardManager.h"

KeyboardManager* KeyboardManager::_singleton = 0;

KeyboardManager::KeyboardManager() {
    initialize();
}

KeyboardManager& KeyboardManager::getInstance() {
    if(_singleton == 0) {
        _singleton = new KeyboardManager;
    }
    return *_singleton;
}

bool KeyboardManager::isKeyDown(unsigned char key) {
    return _keys[tolower(key)];
}

void KeyboardManager::updateKeyState(unsigned char key, bool isDown) {
    _keys[tolower(key)] = isDown;
}

void KeyboardManager::initialize() {
    int i = 0;
    for(i = 0; i <= UCHAR_MAX; i++) {
        _keys[i] = false;
    }
}
