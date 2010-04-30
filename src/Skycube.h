/*
 *  Skycube.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/25/09.
 *
 */

#ifndef NHZ_SKYCUBE_H
#define NHZ_SKYCUBE_H

#include <istream>

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "Renderable.h"

class Skycube : public Renderable {
  public:
    Skycube(const char* north, const char* south, const char* east,
            const char* west, const char* up, const char* down);
    ~Skycube();
    void render() const;
  protected:
    void initialize(const char* north, const char* south, const char* east,
                    const char* west, const char* up, const char* down);
  private:
    static const int NORTH = 0;
    static const int SOUTH = 1;
    static const int EAST  = 2;
    static const int WEST  = 3;
    static const int UP    = 4;
    static const int DOWN  = 5;
    GLuint _textures[6];
    void renderOneSide(GLuint texture) const;
    void renderOneFace() const;
};

#endif
