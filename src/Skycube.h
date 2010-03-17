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
        Skycube(std::istream& north, std::istream& south, std::istream& east,
                std::istream& west, std::istream& up, std::istream& down);
        Skycube(std::istream& north, std::istream& south, std::istream& east,
                std::istream& west, std::istream& up, std::istream& down,
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
        void initialize(std::istream& north, std::istream& south,
                        std::istream& east, std::istream& west,
                        std::istream& up, std::istream& down);
        void initialize(std::istream& north, std::istream& south,
                        std::istream& east, std::istream& west,
                        std::istream& up, std::istream& down,
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
