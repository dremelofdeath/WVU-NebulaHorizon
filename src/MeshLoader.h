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
        virtual Renderable& loadMesh(std::istream& input) = 0;
    protected:
        void processVertex(double x, double y, double z);
        virtual void processVertex(double x, double y, double z, double w);
        void processTextureVertex(double u);
        void processTextureVertex(double u, double v);
        virtual void processTextureVertex(double u, double v, double w);
        virtual void processVertexNormal(double i, double j, double k);
        virtual void processPoint(const std::vector<int>* vertices);
        void processLine(const std::vector<int>* vertices);
        virtual void processLine(const std::vector<int>* v,
                                 const std::vector<int>* vt);
        void processFace(const std::vector<int>* vertices);
        void processFace(const std::vector<int>* v, const std::vector<int>* vt);
        virtual void processFace(const std::vector<int>* v,
                                 const std::vector<int>* vt,
                                 const std::vector<int>* vn);
        void addVertexToList(double x, double y, double z, double w);
        void addTextureVertexToList(double u, double v, double w);
        void addVertexNormalToList(double i, double j, double k);
        Quadruple<double>* getVertex(size_t i);
        Triple<double>* getTextureVertex(size_t i);
        Triple<double>* getVertexNormal(size_t i);
    private:
        std::vector<Quadruple<double>*> _vertexList;
        std::vector<Triple<double>*> _textureVertexList;
        std::vector<Triple<double>*> _vertexNormalList;
};

#endif
