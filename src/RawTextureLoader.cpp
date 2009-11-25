/*
 *  RawTextureLoader.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/25/09.
 *  Copyright 2009 West Virginia University. All rights reserved.
 *
 */

#include <stdexcept>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include "RawTextureLoader.h"

GLuint RawTextureLoader::loadTexture(std::istream& input) {
    throw std::logic_error("must specify width and height for RAW format");
    return 0;
}

GLuint RawTextureLoader::loadTexture(std::istream& input, int w, int h) {
    GLuint texture;
    char data[w*h*3];
    input.read(data, w*h*3);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
    return texture;
}
