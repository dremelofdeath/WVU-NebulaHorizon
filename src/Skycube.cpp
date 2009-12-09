/*
 *  Skycube.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/25/09.
 *
 */

#include <fstream>
#include "Skycube.h"

Skycube::Skycube(const char* north, const char* south, const char* east,
                 const char* west, const char* up, const char* down) {
    initialize(north, south, east, west, up, down);
}

Skycube::Skycube(const char* north, const char* south, const char* east,
                 const char* west, const char* up, const char* down,
                 TextureLoader* loader) {
    initialize(north, south, east, west, up, down, loader);
}

Skycube::Skycube(std::istream& north, std::istream& south, std::istream& east,
                 std::istream& west, std::istream& up, std::istream& down) {
    initialize(north, south, east, west, up, down);
}

Skycube::Skycube(std::istream& north, std::istream& south, std::istream& east,
                 std::istream& west, std::istream& up, std::istream& down,
                 TextureLoader* loader) {
    initialize(north, south, east, west, up, down, loader);
}

void Skycube::setSize(double size) {
    _size = size;
}

void Skycube::render() const {
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glScaled(_size, _size, _size);
    renderOneSide(_northTexture);
    glRotated(90.0, 0.0, 1.0, 0.0);
    renderOneSide(_eastTexture);
    glRotated(90.0, 0.0, 1.0, 0.0);
    renderOneSide(_southTexture);
    glRotated(90.0, 0.0, 1.0, 0.0);
    renderOneSide(_westTexture);
    glRotated(90.0, 0.0, 1.0, 0.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    renderOneSide(_upTexture);
    glRotated(180.0, 1.0, 0.0, 0.0);
    renderOneSide(_downTexture);
}

void Skycube::initialize(const char* north, const char* south, const char* east,
                         const char* west, const char* up, const char* down) {
    TextureLoader* loader = getDefaultTextureLoader();
    initialize(north, south, east, west, up, down, loader);
    delete loader;
}

void Skycube::initialize(const char* north, const char* south, const char* east,
                         const char* west, const char* up, const char* down,
                         TextureLoader* loader) {
    std::ifstream northstr(north);
    std::ifstream southstr(south);
    std::ifstream eaststr(east);
    std::ifstream weststr(west);
    std::ifstream upstr(up);
    std::ifstream downstr(down);
    initialize(northstr, southstr, eaststr, weststr, upstr, downstr, loader);
}

void Skycube::initialize(std::istream& north, std::istream& south,
                         std::istream& east, std::istream& west,
                         std::istream& up, std::istream& down) {
    TextureLoader* loader = getDefaultTextureLoader();
    initialize(north, south, east, west, up, down, loader);
    delete loader;
}

void Skycube::initialize(std::istream& north, std::istream& south,
                         std::istream& east, std::istream& west,
                         std::istream& up, std::istream& down,
                         TextureLoader* loader) {
    setSize(500.0);
    _northTexture = loader->loadTexture(north, 2048, 2048);
    _southTexture = loader->loadTexture(south, 2048, 2048);
    _eastTexture = loader->loadTexture(east, 2048, 2048);
    _westTexture = loader->loadTexture(west, 2048, 2048);
    _upTexture = loader->loadTexture(up, 2048, 2048);
    _downTexture = loader->loadTexture(down, 2048, 2048);
}

Skycube::~Skycube() {
    glDeleteTextures(1, &_northTexture);
    glDeleteTextures(1, &_southTexture);
    glDeleteTextures(1, &_eastTexture);
    glDeleteTextures(1, &_westTexture);
    glDeleteTextures(1, &_upTexture);
    glDeleteTextures(1, &_downTexture);
}

TextureLoader* Skycube::getDefaultTextureLoader() {
    return new RawTextureLoader;
}

void Skycube::renderOneSide(GLuint texture) const {
    glBindTexture(GL_TEXTURE_2D, texture);
    renderOneFace();
}

void Skycube::renderOneFace() const {
    static const GLdouble vlen = 1.0;
    glBegin(GL_QUADS);
    glTexCoord2d(vlen, vlen);
    glVertex3d(-vlen, -vlen, vlen);
    glTexCoord2d(0.0, vlen);
    glVertex3d(vlen, -vlen, vlen);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(vlen, vlen, vlen);
    glTexCoord2d(vlen, 0.0);
    glVertex3d(-vlen, vlen, vlen);
    glEnd();
}
