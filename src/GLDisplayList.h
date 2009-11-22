/*
 *  GLDisplayList.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/21/09.
 *
 */

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "Renderable.h"

#ifndef NHZ_GLDISPLAYLIST_H
#define NHZ_GLDISPLAYLIST_H

class GLDisplayList : public Renderable {
    public:
        GLDisplayList();
        GLDisplayList(GLuint list);
        ~GLDisplayList();
        void render();
        GLuint getList();
    protected:
        void initialize();
        void initialize(GLuint list);
    private:
        GLuint _list;
};

#endif
