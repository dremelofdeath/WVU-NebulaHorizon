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
        Skycube(char* north, char* south, char* east, char* west, char* up,
                char* down);
        Skycube(char* north, char* south, char* east, char* west, char* up,
                char* down, TextureLoader* loader);
        Skycube(std::istream& north, std::istream& south, std::istream& east,
                std::istream& west, std::istream& up, std::istream& down);
        Skycube(std::istream& north, std::istream& south, std::istream& east,
                std::istream& west, std::istream& up, std::istream& down,
                TextureLoader* loader);
        ~Skycube();
        void setSize(double size);
        void render();
    protected:
        void initialize(char* north, char* south, char* east, char* west,
                        char* up, char* down);
        void initialize(char* north, char* south, char* east, char* west,
                        char* up, char* down, TextureLoader* loader);
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
        void renderOneSide(GLuint texture, double xAngle, double yAngle) const;
        void renderOneFace() const;
};

#endif
