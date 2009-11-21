/*
 *  GLMeshLoader.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/20/09.
 *
 */

#include <istream>
#include <vector>

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
        virtual Renderable& loadMesh(std::istream& input) = 0;
    protected:
        void processPoint(const std::vector<int>* vertices);
        void processLine(const std::vector<int>* v,
                         const std::vector<int>* vt);
        void processFace(const std::vector<int>* v,
                         const std::vector<int>* vt,
                         const std::vector<int>* vn);
        void glPrimitivePreamble(GLenum mode);
        void glPrimitiveEpilogue();
        void initialize();
    private:
        GLenum _lastMode;
};

#endif
