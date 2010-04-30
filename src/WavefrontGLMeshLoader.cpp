/*
 *  WavefrontGLMeshLoader.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/21/09.
 *
 */

#include <vector>
#include "WavefrontGLMeshLoader.h"
#include "GLDisplayList.h"
#include "nhz_common.h"

WavefrontGLMeshLoader::~WavefrontGLMeshLoader() {
  cleanup();
}

Renderable* WavefrontGLMeshLoader::loadMesh(std::istream& input) {
  GLDisplayList* mesh = new GLDisplayList;
  glNewList(mesh->getList(), GL_COMPILE);
  parseFile(input);
  glPrimitiveEpilogue();
  glEndList();
  return mesh;
}

void WavefrontGLMeshLoader::parseFile(std::istream& input) {
  while(input.good()) {
    char s[12];
    input.get(s, 12, ' ');
    input.get();
    std::string cmd(s);
    if(cmd == "#") {
      processFileComment(input);
    } else if(cmd == "v" || cmd == "vt" || cmd == "vn") {
      char temp[24];
      double x[4];
      int n = 0;
      while(n < 4) {
        input >> temp;
        x[n] = strtod(temp, 0);
        if(input.fail()) {
          input.clear();
          break;
        }
        if(input.bad()) {
          break;
        }
        n++;
        if(input.peek() == '\n') {
          input.get();
          break;
        }
      }
      if(cmd == "v") {
        switch(n) {
          case 3:
            processVertex(x[0], x[1], x[2]);
            break;
          case 4:
            processVertex(x[0], x[1], x[2], x[3]);
            break;
          default:
            NHZ_ERR("invalid vertex; ignoring\n");
            break;
        }
      }
      if(cmd == "vt") {
        switch(n) {
          case 1:
            processTextureVertex(x[0]);
            break;
          case 2:
            processTextureVertex(x[0], x[1]);
            break;
          case 3:
            processTextureVertex(x[0], x[1], x[2]);
            break;
          default:
            NHZ_ERR("invalid texture vertex; ignoring\n");
            break;
        }
      }
      if(cmd == "vn") {
        switch(n) {
          case 3:
            processVertexNormal(x[0], x[1], x[2]);
            break;
          default:
            NHZ_ERR("invalid vertex normal; ignoring\n");
            break;
        }
      }
    } else if(cmd == "p") {
      std::vector<int> vertices;
      while(input.good()) {
        int i;
        input >> i;
        if(input.fail()) {
          input.clear();
          break;
        }
        if(input.bad()) {
          break;
        }
        vertices.push_back(i);
        if(input.peek() == '\n') {
          input.get();
          break;
        }
      }
      processPoint(&vertices);
    } else if(cmd == "l") {
      std::vector<int> v;
      std::vector<int> vt;
      while(input.good()) {
        char temp[256];
        input >> temp;
        std::string param(temp);
        if(input.fail()) {
          input.clear();
          break;
        }
        if(input.bad()) {
          break;
        }
        std::istringstream iss(param);
        parseParam(iss, v, vt);
        if(input.peek() == '\n') {
          input.get();
          break;
        }
      }
      if(vt.size() == 0) {
        processLine(&v);
      } else {
        processLine(&vt);
      }
    } else if(cmd == "f") {
      std::vector<int> v;
      std::vector<int> vt;
      std::vector<int> vn;
      while(input.good()) {
        char temp[256];
        input >> temp;
        std::string param(temp);
        if(input.fail()) {
          input.clear();
          break;
        }
        if(input.bad()) {
          break;
        }
        std::istringstream iss(param);
        parseParam(iss, v, vt, vn);
        if(input.peek() == '\n') {
          input.get();
          break;
        }
      }
      if(vn.size() == 0) {
        if(vt.size() == 0) {
          processFace(&v);
        } else {
          processFace(&v, &vt);
        }
      } else {
        if(vt.size() == 0) {
          processFace(&v, 0, &vn);
        } else {
          processFace(&v, &vt, &vn);
        }
      }
    } else {
      // it's a command we don't care about, ignore it
      processFileComment(input);
    }
  }
  if(input.bad()) {
    NHZ_ERR("stream went bad during mesh processing\n");
  }
  if(input.fail() && !input.eof()) {
    NHZ_ERR("stream failed, probably means file not found\n");
  }
}

void WavefrontGLMeshLoader::parseParam(std::istringstream& param,
    std::vector<int>& v,
    std::vector<int>& vt) {
  int x[2];
  int n = 0;
  char sep = '/';
  while(param.good() && n < 2 && sep == '/') {
    param >> x[n];
    x[n]--;
    if(param.bad() || param.fail()) {
      break;
    }
    n++;
    param >> sep;
  }
  if(!param.fail() && sep != '/') {
    NHZ_ERR("invalid separator; ignoring remaining attributes\n");
  }
  if(param.bad()) {
    NHZ_ERR("failed to parse param (bad stream); dropping\n");
  } else {
    switch(n) {
      case 2:
        vt.push_back(x[1]);
      case 1:
        v.push_back(x[0]);
        break;
      default:
        NHZ_ERR("invalid parameter; ignoring\n");
        break;
    }
  }
}

void WavefrontGLMeshLoader::parseParam(std::istringstream& param,
    std::vector<int>& v,
    std::vector<int>& vt,
    std::vector<int>& vn) {
  int x;
  parseParam(param, v, vt);
  if(param.good()) {
    param >> x;
    x--;
    if(param.bad()) {
      NHZ_ERR("stream went bad; dropping final attribute\n");
    } else if(param.fail()) {
      param.clear();
    } else {
      vn.push_back(x);
    }
  }
}

void WavefrontGLMeshLoader::processFileComment(std::istream& input) {
  char s[256];
  input.getline(s, 256);
  if(input.fail()) {
    if(!input.eof()) {
      input.clear();
      input.get();
      if(input.fail()) {
        NHZ_ERR("unstoppable failure in processFileComment()\n");
      }
    }
  }
  if(input.bad()) {
    NHZ_ERR("getline() caused bad stream in processFileComment()\n");
  }
}
