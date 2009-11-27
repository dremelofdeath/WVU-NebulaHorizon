#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include "handlers.h"
#include "RenderQueue.h"
#include "KeyboardManager.h"
#include "WavefrontGLMeshLoader.h"

static GLsizei winWidth = 800, winHeight = 600;
static int window_id_main = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(KeyboardManager::getInstance().isKeyDown('j')) {
        glRotated(0.05, 0.0, 1.0, 0.0);
    }
    if(KeyboardManager::getInstance().isKeyDown('l')) {
        glRotated(-0.05, 0.0, 1.0, 0.0);
    }
    if(KeyboardManager::getInstance().isKeyDown('i')) {
        glRotated(0.05, 1.0, 0.0, 0.0);
    }
    if(KeyboardManager::getInstance().isKeyDown('k')) {
        glRotated(-0.05, 1.0, 0.0, 0.0);
    }
    glPushMatrix();
    RenderQueue::getInstance()->render();
    glPopMatrix();
    glutSwapBuffers();
}

void idle() {
	static int last_time = 0;
	int time = glutGet(GLUT_ELAPSED_TIME);
    // if we overflow, last_time will be greater than time
	int elapsed = last_time <= time ? time-last_time : time+last_time;
	last_time = time;
    RenderQueue::getInstance()->idle(elapsed);
    glutPostRedisplay();
}

void handle_keyboard(unsigned char key, int x, int y) {
    KeyboardManager::getInstance().updateKeyState(key, true);
}

void handle_keyboard_up(unsigned char key, int x, int y) {
    KeyboardManager::getInstance().updateKeyState(key, false);
}

void handle_special_key(int key, int x, int y) {
    //RenderQueue::getInstance()->handleSpecialKey(key, x, y);
}

void handle_mouse_event(int button, int state, int x, int y) {
    RenderQueue::getInstance()->handleMouseEvent(button, state, x, y);
}

void handle_mouse_drag(int x, int y) {
    RenderQueue::getInstance()->handleMouseDrag(x, y);
}

void handle_mouse_motion(int x, int y) {
    RenderQueue::getInstance()->handleMouseMotion(x, y);
}

void update_projection(GLsizei w, GLsizei h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w/(double)h, 0.1, 1000);
}

static void reshape(GLsizei w, GLsizei h) {
    winWidth = w;
    winHeight = h;
    update_projection(w, h);
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void create_callbacks() {
    glutDisplayFunc(&display);
    glutIdleFunc(&idle);
    glutReshapeFunc(&reshape);
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(&handle_keyboard);
    glutKeyboardUpFunc(&handle_keyboard_up);
    glutSpecialFunc(&handle_special_key);
    glutMouseFunc(&handle_mouse_event);
    glutMotionFunc(&handle_mouse_drag);
    glutPassiveMotionFunc(&handle_mouse_motion);
}

void exit_callback() {
    RenderQueue::getInstance()->clear();
    glutDestroyWindow(window_id_main);
}

int create_window(const char *title, int xpos, int ypos, int ww, int wh) {
    int ret = 0;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(xpos, ypos);
    glutInitWindowSize(ww, wh);
    ret = glutCreateWindow(title);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
    return ret;
}

void init_opengl() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    update_projection(winWidth, winHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void set_window_id(int id) {
    window_id_main = id;
}
