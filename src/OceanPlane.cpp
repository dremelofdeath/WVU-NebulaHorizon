/*
 * OceanPlane.cpp
 * Nebula Horizon
 *
 * Created by Zachary Murray on 4/30/2010 7:12:02 AM Eastern Daylight Time
 *
 */

#include "RenderQueue.h"
#include "OceanPlane.h"

#include <GL/glut.h>

OceanPlane::OceanPlane() {
  initialize();
}

OceanPlane::~OceanPlane() {
  glDeleteRenderbuffersEXT(1, &_rbID);
  glDeleteFramebuffersEXT(1, &_fboID);
  glDeleteTextures(1, &_reflectionTextureID);
}

void OceanPlane::render() const {
  Renderable::render();
  glEnable(GL_TEXTURE_2D);
  //glDisable(GL_LIGHTING);
  glBindTexture(GL_TEXTURE_2D, _reflectionTextureID);
  glColor3f(0.0f, 0.4f, 0.5f);
  glBegin(GL_QUADS);
  glTexCoord2i(0, 0);
  glVertex3i(-25, -3, -25);
  glTexCoord2i(0, 1);
  glVertex3i(-25, -3, 25);
  glTexCoord2i(1, 1);
  glVertex3i(25, -3, 25);
  glTexCoord2i(1, 0);
  glVertex3i(25, -3, -25);
  glEnd();
  glPushMatrix();
  glTranslatef(-1.5f, 0.5f, -6.0f);
  glutSolidTeapot(1.0);
  glPopMatrix();
}

void OceanPlane::idle(const int elapsed) {
  // I think this should probably end up in the render() call, but since it's
  // still irritatingly a const method, you can't disable renders from within
  // render.
  disableRendering();
  glPushAttrib(GL_VIEWPORT_BIT);
  glViewport(0, 0, _wh, _wh);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fboID);
  glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glPushMatrix();
  glTranslatef(0.0f, -5.0f, -23.0f);
  RenderQueue::getInstance()->render();
  glPopMatrix();
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
  glDrawBuffer(GL_BACK);
  glPopAttrib();
  resumeRendering();
}

bool OceanPlane::isRendering() const {
  return _isRendering;
}

void OceanPlane::disableRendering() {
  _isRendering = false;
}

void OceanPlane::resumeRendering() {
  _isRendering = true;
}

void OceanPlane::initialize() {
  _isRendering = true;
  glGenTextures(1, &_reflectionTextureID);
  glBindTexture(GL_TEXTURE_2D, _reflectionTextureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // NULL means reserve texture memory, but texels are undefined
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _wh, _wh, 0, GL_BGRA,
               GL_UNSIGNED_BYTE, NULL);
  glGenFramebuffersEXT(1, &_fboID);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fboID);
  glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                            GL_TEXTURE_2D, _reflectionTextureID, 0);
  glGenRenderbuffersEXT(1, &_rbID);
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _rbID);
  glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, _wh, _wh);
  glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
                               GL_RENDERBUFFER_EXT, _rbID);
  GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
  switch(status) {
    case GL_FRAMEBUFFER_COMPLETE_EXT:
      break;
    default:
      NHZ_ERR("Framebuffer configuration not supported!\n");
      break;
  }
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}
