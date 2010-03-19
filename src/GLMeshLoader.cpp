/*
 *  GLMeshLoader.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/20/09.
 *
 */

#include "GLMeshLoader.h"

GLMeshLoader::GLMeshLoader() : MeshLoader() {
  initialize();
}

GLMeshLoader::~GLMeshLoader() {
  cleanup();
}

void GLMeshLoader::processPoint(std::vector<int>* const vertices) {
  MeshLoader::processPoint(vertices);
  std::vector<int>::const_iterator vector_it = vertices->begin();
  glPrimitivePreamble(GL_POINTS);
  while(vector_it != vertices->end()) {
    Quadruple<double>& vi = *getVertex(*vector_it);
    glVertex4d(vi[0], vi[1], vi[2], vi[3]);
    vector_it++;
  }
}

void GLMeshLoader::processLine(std::vector<int>* const vertices) {
  processLine(vertices, 0);
}

void GLMeshLoader::processLine(std::vector<int>* const v,
                               std::vector<int>* const vt) {
  MeshLoader::processLine(v, vt);
  std::vector<int>::const_iterator vertex_it = v->begin();
  std::vector<int>::const_iterator texture_it;
  if(vt != 0) {
    texture_it = vt->begin();
  }
  glPrimitivePreamble(GL_LINE_STRIP);
  while(vertex_it != v->end()) {
    Quadruple<double>& vi = *getVertex(*vertex_it);
    if(vt != 0) {
      Triple<double>& vti = *getTextureVertex(*texture_it);
      glTexCoord3d(vti[0], vti[1], vti[2]);
      texture_it++;
    }
    glVertex4d(vi[0], vi[1], vi[2], vi[3]);
    vertex_it++;
  }
}

void GLMeshLoader::processFace(std::vector<int>* const vertices) {
  processFace(vertices, 0);
}

void GLMeshLoader::processFace(std::vector<int>* const v,
                               std::vector<int>* const vt) {
  processFace(v, vt, 0);
}

void GLMeshLoader::processFace(std::vector<int>* const v,
                               std::vector<int>* const vt,
                               std::vector<int>* const vn) {
  MeshLoader::processFace(v, vt, vn);
  std::vector<int>::const_iterator vertex_it = v->begin();
  std::vector<int>::const_iterator texture_it;
  std::vector<int>::const_iterator normal_it;
  if(vt != 0) {
    texture_it = vt->begin();
  }
  if(vn != 0) {
    normal_it = vn->begin();
  }
  GLenum mode = GL_POLYGON;
  switch(v->size()) {
    case 3:
      mode = GL_TRIANGLES;
      break;
    case 4:
      mode = GL_QUADS;
      break;
  }
  glPrimitivePreamble(mode);
  while(vertex_it != v->end()) {
    Quadruple<double>& vi = *getVertex(*vertex_it);
    if(vt != 0) {
      Triple<double>& vti = *getTextureVertex(*texture_it);
      glTexCoord3d(vti[0], vti[1], vti[2]);
      texture_it++;
    }
    if(vn != 0) {
      Triple<double>& vni = *getVertexNormal(*normal_it);
      glNormal3d(vni[0], vni[1], vni[2]);
      normal_it++;
    }
    glVertex4d(vi[0], vi[1], vi[2], vi[3]);
    vertex_it++;
  }
}

void GLMeshLoader::glPrimitivePreamble(GLenum mode) {
  if(_lastMode != mode) {
    glPrimitiveEpilogue();
    _lastMode = mode;
    glBegin(mode);
  }
}

void GLMeshLoader::glPrimitiveEpilogue() {
  if(_lastMode != -1) {
    glEnd();
  }
}

void GLMeshLoader::initialize() {
  _lastMode = -1;
}
