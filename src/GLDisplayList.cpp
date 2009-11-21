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

void GLDisplayList::render() {
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
