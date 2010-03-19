/*
 *  RawTextureLoader.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/25/09.
 *
 */

#include <stdexcept>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#endif

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
  static int x = 0;
  GLuint texture;
  char *data = (char *)malloc(sizeof(char)*w*h*3);
  ++x;
  if(input.bad()) {
    std::cerr << "bad input" << std::endl;
  };
  if(input.fail()) {
    std::cerr << "fail input: " << x << std::endl;
  };
  if(input.eof()) {
    std::cerr << "eof input" << std::endl;
  };
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
  free(data);
  return texture;
}
