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
#include "TextureLoader.h"
#include "RawTextureLoader.h"

class Skycube : public Renderable {
  public:
    Skycube(const char* north, const char* south, const char* east,
            const char* west, const char* up, const char* down);
    Skycube(const char* north, const char* south, const char* east,
            const char* west, const char* up, const char* down,
            TextureLoader* loader);
    Skycube(std::ifstream& north, std::ifstream& south, std::ifstream& east,
            std::ifstream& west, std::ifstream& up, std::ifstream& down);
    Skycube(std::ifstream& north, std::ifstream& south, std::ifstream& east,
            std::ifstream& west, std::ifstream& up, std::ifstream& down,
            TextureLoader* loader);
    ~Skycube();
    void setSize(double size);
    void render() const;
  protected:
    void initialize(const char* north, const char* south, const char* east,
                    const char* west, const char* up, const char* down);
    void initialize(const char* north, const char* south, const char* east,
                    const char* west, const char* up, const char* down,
                    TextureLoader* loader);
    void initialize(std::ifstream& north, std::ifstream& south,
                    std::ifstream& east, std::ifstream& west,
                    std::ifstream& up, std::ifstream& down);
    void initialize(std::ifstream& north, std::ifstream& south,
                    std::ifstream& east, std::ifstream& west,
                    std::ifstream& up, std::ifstream& down,
                    TextureLoader* loader);
    TextureLoader* getDefaultTextureLoader();
  private:
    GLuint _northTexture, _southTexture;
    GLuint _eastTexture, _westTexture;
    GLuint _upTexture, _downTexture;
    double _size;
    void renderOneSide(GLuint texture) const;
    void renderOneFace() const;
};

#endif
