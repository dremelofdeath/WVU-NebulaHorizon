/*
 *  Skycube.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/25/09.
 *
 */

#include <fstream>
#include "Skycube.h"

Skycube::Skycube(char* north, char* south, char* east, char* west, char* up,
                 char* down) {
    initialize(north, south, east, west, up, down);
}

Skycube::Skycube(char* north, char* south, char* east, char* west, char* up,
                 char* down, TextureLoader* loader) {
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

void Skycube::render() {
    glScaled(_size, _size, _size);
    renderOneSide(_northTexture, 0.0, 0.0);
    renderOneSide(_southTexture, 0.0, 180.0);
    renderOneSide(_eastTexture, 0.0, 90.0);
    renderOneSide(_westTexture, 0.0, 270.0);
    renderOneSide(_upTexture, 90.0, 0.0);
    renderOneSide(_downTexture, 180.0, 0.0);
}

void Skycube::initialize(char* north, char* south, char* east, char* west,
                         char* up, char* down) {
    TextureLoader* loader = getDefaultTextureLoader();
    initialize(north, south, east, west, up, down, loader);
    delete loader;
}

void Skycube::initialize(char* north, char* south, char* east, char* west,
                         char* up, char* down, TextureLoader* loader) {
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
    // TODO: wake up and make this happen
    setSize(100.0);
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

void Skycube::renderOneSide(GLuint texture, double xAngle, double yAngle) const {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture);
    glRotated(xAngle, 1.0, 0.0, 0.0);
    glRotated(yAngle, 0.0, 1.0, 0.0);
    renderOneFace();
    glPopMatrix();
}

void Skycube::renderOneFace() const {
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(-0.5, -0.5, 0.5);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(0.5, -0.5, 0.5);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(0.5, 0.5, 0.5);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(-0.5, 0.5, 0.5);
    glEnd();
}
