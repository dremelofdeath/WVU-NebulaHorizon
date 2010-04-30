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

#include <IL/il.h>
#include <IL/ilu.h>

#include "nhz_common.h"

Skycube::Skycube(const char* north, const char* south, const char* east,
                 const char* west, const char* up, const char* down) {
  initialize(north, south, east, west, up, down);
}

Skycube::~Skycube() {
  glDeleteTextures(6, _textures);
}

void Skycube::render() const {
  static const GLint vlen = 500;

  glDisable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);

  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  glBindTexture(GL_TEXTURE_2D, _textures[NORTH]);
  glBegin(GL_QUADS);
  glTexCoord2i(1, 0);
  glVertex3i(vlen, vlen, -vlen);
  glTexCoord2i(0, 0);
  glVertex3i(-vlen, vlen, -vlen);
  glTexCoord2i(0, 1);
  glVertex3i(-vlen, -vlen, -vlen);
  glTexCoord2i(1, 1);
  glVertex3i(vlen, -vlen, -vlen);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, _textures[WEST]);
  glBegin(GL_QUADS);
  glTexCoord2i(1, 0);
  glVertex3i(-vlen, vlen, -vlen);
  glTexCoord2i(0, 0);
  glVertex3i(-vlen, vlen, vlen);
  glTexCoord2i(0, 1);
  glVertex3i(-vlen, -vlen, vlen);
  glTexCoord2i(1, 1);
  glVertex3i(-vlen, -vlen, -vlen);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, _textures[SOUTH]);
  glBegin(GL_QUADS);
  glTexCoord2i(1, 0);
  glVertex3i(-vlen, vlen, vlen);
  glTexCoord2i(0, 0);
  glVertex3i(vlen, vlen, vlen);
  glTexCoord2i(0, 1);
  glVertex3i(vlen, -vlen, vlen);
  glTexCoord2i(1, 1);
  glVertex3i(-vlen, -vlen, vlen);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, _textures[EAST]);
  glBegin(GL_QUADS);
  glTexCoord2i(1, 0);
  glVertex3i(vlen, vlen, vlen);
  glTexCoord2i(0, 0);
  glVertex3i(vlen, vlen, -vlen);
  glTexCoord2i(0, 1);
  glVertex3i(vlen, -vlen, -vlen);
  glTexCoord2i(1, 1);
  glVertex3i(vlen, -vlen, vlen);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, _textures[DOWN]);
  glBegin(GL_QUADS);
  glTexCoord2i(1, 0);
  glVertex3i(vlen, -vlen, -vlen);
  glTexCoord2i(0, 0);
  glVertex3i(-vlen, -vlen, -vlen);
  glTexCoord2i(0, 1);
  glVertex3i(-vlen, -vlen, vlen);
  glTexCoord2i(1, 1);
  glVertex3i(vlen, -vlen, vlen);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, _textures[UP]);
  glBegin(GL_QUADS);
  glTexCoord2i(1, 0);
  glVertex3i(vlen, vlen, vlen);
  glTexCoord2i(0, 0);
  glVertex3i(-vlen, vlen, vlen);
  glTexCoord2i(0, 1);
  glVertex3i(-vlen, vlen, -vlen);
  glTexCoord2i(1, 1);
  glVertex3i(vlen, vlen, -vlen);
  glEnd();

  glPopMatrix();
}

static void il_skycube_upload(const char* imagefile, GLuint texture) {
  wchar_t wfile[100];
  ILuint currentImage;

#ifdef _DEBUG
  ILenum errorcode;
#endif

  ilGenImages(1, &currentImage);
  ilBindImage(currentImage);

#ifdef WIN32
  mbstowcs_s(NULL, (wchar_t*)wfile, strlen(imagefile)+1, imagefile, _TRUNCATE);
#else
  mbstowcs(wfile, imagefile, 100);
#endif

  ilLoadImage(wfile);
  ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP),
               ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
               ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

  ilDeleteImages(1, &currentImage);

#ifdef _DEBUG
  while((errorcode = ilGetError()) != IL_NO_ERROR) {
    wchar_t* err = (wchar_t*)iluErrorString(errorcode);
    char temp[100];
#ifdef WIN32
    wcstombs_s(NULL, (char*)temp, wcslen(err)+1, err, _TRUNCATE);
#else
    wcstombs(temp, err, 100);
#endif
    NHZ_ERR("%s(%i) error: %s\n", imagefile, texture, temp);
#endif
  }
}

void Skycube::initialize(const char* north, const char* south, const char* east,
                         const char* west, const char* up, const char* down) {
  glGenTextures(6, _textures);
  il_skycube_upload(north, _textures[NORTH]);
  il_skycube_upload(south, _textures[SOUTH]);
  il_skycube_upload(east, _textures[EAST]);
  il_skycube_upload(west, _textures[WEST]);
  il_skycube_upload(up, _textures[UP]);
  il_skycube_upload(down, _textures[DOWN]);
}
