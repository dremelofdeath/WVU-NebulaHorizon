/*
 *  GLDisplayList.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/21/09.
 *
 */

#include "GLDisplayList.h"

GLDisplayList::GLDisplayList() {
    initialize();
}

GLDisplayList::GLDisplayList(GLuint list) {
    initialize(list);
}

GLDisplayList::~GLDisplayList() {
    glDeleteLists(_list, 1);
}

void GLDisplayList::render() const {
    glCallList(_list);
}

GLuint GLDisplayList::getList() {
    return _list;
}

void GLDisplayList::initialize() {
    initialize(glGenLists(1));
}

void GLDisplayList::initialize(GLuint list) {
    _list = list;
}
