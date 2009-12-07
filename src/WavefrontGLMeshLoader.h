/*
 *  WavefrontGLMeshLoader.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/21/09.
 *
 */

#include <istream>
#include <string>
#include <sstream>
#include "GLMeshLoader.h"
#include "Renderable.h"

#ifndef NHZ_WAVEFRONTGLMESHLOADER_H
#define NHZ_WAVEFRONTGLMESHLOADER_H

class WavefrontGLMeshLoader : public GLMeshLoader {
    public:
        ~WavefrontGLMeshLoader();
        Renderable* loadMesh(std::istream& input);
    protected:
        void parseFile(std::istream& input);
        void parseParam(std::istringstream& param, std::vector<int>& v,
                        std::vector<int>& vt);
        void parseParam(std::istringstream& param, std::vector<int>& v,
                        std::vector<int>& vt, std::vector<int>& vn);
        void processFileComment(std::istream& input);
};

#endif
