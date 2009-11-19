/*
 *  MeshLoader.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/18/09.
 *
 */

#include <stdexcept>
#include "MeshLoader.h"

void MeshLoader::processVertex(double x, double y, double z) {
    processVertex(x, y, z, 1.0);
}

void MeshLoader::processVertex(double x, double y, double z, double w) {
    // default implementation does nothing
}

void MeshLoader::processTextureVertex(double u) {
    processTextureVertex(u, 0.0);
}

void MeshLoader::processTextureVertex(double u, double v) {
    processTextureVertex(u, v, 0.0);
}

void MeshLoader::processTextureVertex(double u, double v, double w) {
    // default implementation does nothing
}

void MeshLoader::processVertexNormal(double i, double j, double k) {
    // default implementation does nothing
}

void MeshLoader::processPoint(const std::vector<int>* vertices) {
    // default implementation does nothing
    if(vertices == 0) {
        throw std::invalid_argument("vertices");
    } else if(vertices->size() < 1) {
        throw std::length_error("vertices");
    }
}

void MeshLoader::processLine(const std::vector<int>* vertices) {
    processLine(vertices, 0);
}

void MeshLoader::processLine(const std::vector<int>* v,
                             const std::vector<int>* vt) {
    // default implementation does nothing but check for errors
    if(v == 0) {
        throw std::invalid_argument("v");
    } else if(v->size() < 2) {
        throw std::length_error("v");
    }
    if(vt != 0 && v->size() != vt->size()) {
        throw std::length_error("vt");
    }
}

void MeshLoader::processFace(const std::vector<int>* vertices) {
    processFace(vertices, 0);
}

void MeshLoader::processFace(const std::vector<int>* v,
                             const std::vector<int>* vt) {
    processFace(v, vt, 0);
}

void MeshLoader::processFace(const std::vector<int>* v,
                             const std::vector<int>* vt,
                             const std::vector<int>* vn) {
    // default implementation does nothing but check for errors
    if(v == 0) {
        throw std::invalid_argument("v");
    } else if(v->size() < 3) {
        throw std::length_error("v");
    }
    if(vt != 0 && v->size() != vt->size()) {
        throw std::length_error("vt");
    }
    if(vn != 0 && v->size() != vn->size()) {
        throw std::length_error("vn");
    }
}
