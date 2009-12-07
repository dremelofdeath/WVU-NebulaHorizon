/*
 *  MeshLoader.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/18/09.
 *
 */

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "Renderable.h"
#include "Triple.h"
#include "Quadruple.h"

#ifndef NHZ_MESHLOADER_H
#define NHZ_MESHLOADER_H

class MeshLoader {
    public:
        ~MeshLoader();
        virtual Renderable* loadMesh(std::istream& input) = 0;
    protected:
        void processVertex(double x, double y, double z);
        virtual void processVertex(double x, double y, double z, double w);
        void processTextureVertex(double u);
        void processTextureVertex(double u, double v);
        virtual void processTextureVertex(double u, double v, double w);
        virtual void processVertexNormal(double i, double j, double k);
        virtual void processPoint(std::vector<int>* const vertices);
        void processLine(std::vector<int>* const vertices);
        virtual void processLine(std::vector<int>* const v,
                                 std::vector<int>* const vt);
        void processFace(std::vector<int>* const vertices);
        void processFace(std::vector<int>* const v, std::vector<int>* const vt);
        virtual void processFace(std::vector<int>* const v,
                                 std::vector<int>* const vt,
                                 std::vector<int>* const vn);
        void addVertexToList(double x, double y, double z, double w);
        void addTextureVertexToList(double u, double v, double w);
        void addVertexNormalToList(double i, double j, double k);
        Quadruple<double>* getVertex(size_t i);
        Triple<double>* getTextureVertex(size_t i);
        Triple<double>* getVertexNormal(size_t i);
        void cleanup();
    private:
        std::vector<Quadruple<double>*> _vertexList;
        std::vector<Triple<double>*> _textureVertexList;
        std::vector<Triple<double>*> _vertexNormalList;
};

#endif
