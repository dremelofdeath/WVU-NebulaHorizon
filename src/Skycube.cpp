/*
 *  Skycube.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/25/09.
 *
 */

#include <fstream>
#include "Skycube.h"

#ifdef __APPLE__
#include <OpenGL/glext.h>
#else
#include <GL/glext.h>
#endif

Skycube::Skycube(const char* north, const char* south, const char* east,
                 const char* west, const char* up, const char* down) {
  initialize(north, south, east, west, up, down);
}

Skycube::Skycube(const char* north, const char* south, const char* east,
                 const char* west, const char* up, const char* down,
                 TextureLoader* loader) {
  initialize(north, south, east, west, up, down, loader);
}

Skycube::Skycube(std::ifstream& north, std::ifstream& south, std::ifstream& east,
                 std::ifstream& west, std::ifstream& up, std::ifstream& down) {
  initialize(north, south, east, west, up, down);
}

Skycube::Skycube(std::ifstream& north, std::ifstream& south, std::ifstream& east,
                 std::ifstream& west, std::ifstream& up, std::ifstream& down,
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
  std::ifstream northstr(north, std::ios::in | std::ios::binary);
  std::ifstream southstr(south, std::ios::in | std::ios::binary);
  std::ifstream eaststr(east, std::ios::in | std::ios::binary);
  std::ifstream weststr(west, std::ios::in | std::ios::binary);
  std::ifstream upstr(up, std::ios::in | std::ios::binary);
  std::ifstream downstr(down, std::ios::in | std::ios::binary);

  initialize(northstr, southstr, eaststr, weststr, upstr, downstr, loader);
}

void Skycube::initialize(std::ifstream& north, std::ifstream& south,
                         std::ifstream& east, std::ifstream& west,
                         std::ifstream& up, std::ifstream& down) {
  TextureLoader* loader = getDefaultTextureLoader();
  initialize(north, south, east, west, up, down, loader);
  delete loader;
}

void Skycube::initialize(std::ifstream& north, std::ifstream& south,
                         std::ifstream& east, std::ifstream& west,
                         std::ifstream& up, std::ifstream& down,
                         TextureLoader* loader) {
  setSize(500.0);
  _northTexture = loader->loadTexture(north, 2048, 2048);
  north.close();
  _southTexture = loader->loadTexture(south, 2048, 2048);
  south.close();
  _eastTexture = loader->loadTexture(east, 2048, 2048);
  east.close();
  _westTexture = loader->loadTexture(west, 2048, 2048);
  west.close();
  _upTexture = loader->loadTexture(up, 2048, 2048);
  up.close();
  _downTexture = loader->loadTexture(down, 2048, 2048);
  down.close();
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
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
