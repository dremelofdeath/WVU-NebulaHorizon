/*
 *  WavefrontGLMeshLoader.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/21/09.
 *
 */

#include <vector>
#include "WavefrontGLMeshLoader.h"
#include "GLDisplayList.h"

Renderable* WavefrontGLMeshLoader::loadMesh(std::istream& input) {
    GLDisplayList* mesh = new GLDisplayList;
    glNewList(mesh->getList(), GL_COMPILE);
    parseFile(input);
    glPrimitiveEpilogue();
    glEndList();
    return mesh;
}

void WavefrontGLMeshLoader::parseFile(std::istream& input) {
    while(input.good()) {
        char s[12];
        input.get(s, 12, ' ');
        input.get();
        std::string cmd(s);
        if(cmd == "#") {
            processFileComment(input);
        } else if(cmd == "v" || cmd == "vt" || cmd == "vn") {
            char temp[24];
            double x[4];
            int n = 0;
            while(n < 4) {
                input >> temp;
                x[n] = strtod(temp, 0);
                if(input.fail()) {
                    input.clear();
                    break;
                }
                if(input.bad()) {
                    break;
                }
                n++;
                if(input.peek() == '\n') {
                    input.get();
                    break;
                }
            }
            if(cmd == "v") {
                switch(n) {
                    case 3:
                        processVertex(x[0], x[1], x[2]);
                        break;
                    case 4:
                        processVertex(x[0], x[1], x[2], x[3]);
                        break;
                    default:
                        std::cerr << "invalid vertex; ignoring" << std::endl;
                        break;
                }
            }
            if(cmd == "vt") {
                switch(n) {
                    case 1:
                        processTextureVertex(x[0]);
                        break;
                    case 2:
                        processTextureVertex(x[0], x[1]);
                        break;
                    case 3:
                        processTextureVertex(x[0], x[1], x[2]);
                        break;
                    default:
                        std::cerr << "invalid texture vertex; ignoring";
                        std::cerr << std::endl;
                        break;
                }
            }
            if(cmd == "vn") {
                switch(n) {
                    case 3:
                        processVertexNormal(x[0], x[1], x[2]);
                        break;
                    default:
                        std::cerr << "invalid vertex normal; ignoring";
                        std::cerr << std::endl;
                        break;
                }
            }
        } else if(cmd == "p") {
            std::vector<int> vertices;
            while(input.good()) {
                int i;
                input >> i;
                if(input.fail()) {
                    input.clear();
                    break;
                }
                if(input.bad()) {
                    break;
                }
                vertices.push_back(i);
                if(input.peek() == '\n') {
                    input.get();
                    break;
                }
            }
            processPoint(&vertices);
        } else if(cmd == "l") {
            std::vector<int> v;
            std::vector<int> vt;
            while(input.good()) {
                char temp[256];
                input >> temp;
                std::string param(temp);
                if(input.fail()) {
                    input.clear();
                    break;
                }
                if(input.bad()) {
                    break;
                }
                std::istringstream iss(param);
                parseParam(iss, v, vt);
                if(input.peek() == '\n') {
                    input.get();
                    break;
                }
            }
            if(vt.size() == 0) {
                processLine(&v);
            } else {
                processLine(&vt);
            }
        } else if(cmd == "f") {
            std::vector<int> v;
            std::vector<int> vt;
            std::vector<int> vn;
            while(input.good()) {
                char temp[256];
                input >> temp;
                std::string param(temp);
                if(input.fail()) {
                    input.clear();
                    break;
                }
                if(input.bad()) {
                    break;
                }
                std::istringstream iss(param);
                parseParam(iss, v, vt, vn);
                if(input.peek() == '\n') {
                    input.get();
                    break;
                }
            }
            if(vn.size() == 0) {
                if(vt.size() == 0) {
                    processFace(&v);
                } else {
                    processFace(&v, &vt);
                }
            } else {
                if(vt.size() == 0) {
                    processFace(&v, 0, &vn);
                } else {
                    processFace(&v, &vt, &vn);
                }
            }
        } else {
            // it's a command we don't care about, ignore it
            processFileComment(input);
        }
    }
    if(input.bad()) {
        std::cerr << "stream went bad during mesh processing (";
        std::cerr << __FILE__ << ", line " << __LINE__ << ")" << std::endl;
    }
}

void WavefrontGLMeshLoader::parseParam(std::istringstream& param,
                                       std::vector<int>& v,
                                       std::vector<int>& vt) {
    int x[2];
    int n = 0;
    char sep = '/';
    while(param.good() && n < 2 && sep == '/') {
        char temp[128];
        param >> temp;
        x[n] = atoi(temp)-1;
        if(param.bad() || param.fail()) {
            break;
        }
        n++;
        param >> sep;
    }
    if(!param.fail() && sep != '/') {
        std::cerr << "invalid separator; ignoring remaining attributes";
        std::cerr << std::endl;
    }
    if(param.bad()) {
        std::cerr << "failed to parse param (bad stream); dropping ";
        std::cerr << "(" << __FILE__ << ", line " << __LINE__ << std::endl;
    } else {
        switch(n) {
            case 2:
                vt.push_back(x[1]);
            case 1:
                v.push_back(x[0]);
                break;
            default:
                std::cerr << "invalid parameter; ignoring (" << __FILE__;
                std::cerr << ", line " << __LINE__ << ")" << std::endl;
                break;
        }
    }
}

void WavefrontGLMeshLoader::parseParam(std::istringstream& param,
                                       std::vector<int>& v,
                                       std::vector<int>& vt,
                                       std::vector<int>& vn) {
    int x;
    parseParam(param, v, vt);
    if(param.good()) {
        param >> x;
        x--;
        if(param.bad()) {
            std::cerr << "stream went bad; dropping final attribute";
            std::cerr << std::endl;
        } else if(param.fail()) {
            param.clear();
        } else {
            vn.push_back(x);
        }
    }
}

void WavefrontGLMeshLoader::processFileComment(std::istream& input) {
    char s[256];
    input.getline(s, 256);
    if(input.fail()) {
        if(!input.eof()) {
            input.clear();
            input.get();
            if(input.fail()) {
                std::cerr << "unstoppable failure in processFileComment()";
                std::cerr << std::endl;
            }
        }
    }
    if(input.bad()) {
        std::cerr << "getline() caused bad stream in processFileComment()";
        std::cerr << std::endl;
    }
}
