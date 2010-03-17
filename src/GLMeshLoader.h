/*
 *  GLMeshLoader.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/20/09.
 *
 */

#include <istream>
#include <vector>

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "MeshLoader.h"

#ifndef NHZ_GLMESHLOADER_H
#define NHZ_GLMESHLOADER_H

class GLMeshLoader : public MeshLoader {
    public:
        GLMeshLoader();
        ~GLMeshLoader();
        virtual Renderable* loadMesh(std::istream& input) = 0;
    protected:
        void processPoint(std::vector<int>* const vertices);
        void processLine(std::vector<int>* const vertices);
        void processLine(std::vector<int>* const v,
                         std::vector<int>* const vt);
        void processFace(std::vector<int>* const vertices);
        void processFace(std::vector<int>* const v, std::vector<int>* const vt);
        void processFace(std::vector<int>* const v,
                         std::vector<int>* const vt,
                         std::vector<int>* const vn);
        void glPrimitivePreamble(GLenum mode);
        void glPrimitiveEpilogue();
        void initialize();
    private:
        GLenum _lastMode;
};

#endif
