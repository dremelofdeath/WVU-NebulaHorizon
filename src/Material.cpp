/*
 *  Material.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 12/3/09.
 *  Copyright 2009 West Virginia University. All rights reserved.
 *
 */

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "Material.h"

void Material::setAmbientMaterial(const float (& material)[4]) {
    for(int i = 0; i < 4; i++) {
        _ambient[i] = material[i];
    }
}

void Material::setDiffuseMaterial(const float (& material)[4]) {
    for(int i = 0; i < 4; i++) {
        _diffuse[i] = material[i];
    }
}

void Material::setSpecularMaterial(const float (& material)[4]) {
    for(int i = 0; i < 4; i++) {
        _specular[i] = material[i];
    }
}

void Material::setShininess(const float shininess) {
    _shininess = shininess;
}

void Material::initialize() {
    _ambient[0] = 0.0;
    _ambient[1] = 0.0;
    _ambient[2] = 0.0;
    _ambient[3] = 1.0;
    _diffuse[0] = 0.0;
    _diffuse[1] = 0.0;
    _diffuse[2] = 0.0;
    _diffuse[3] = 1.0;
    _specular[0] = 0.0;
    _specular[1] = 0.0;
    _specular[2] = 0.0;
    _specular[3] = 1.0;
    _shininess = 1.0;
}

void Material::useMaterial() const {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);
}
