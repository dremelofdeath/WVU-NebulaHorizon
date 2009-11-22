#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "RenderQueue.h"
#include "MeshLoader.h"
#include "WavefrontGLMeshLoader.h"

static GLsizei winWidth = 800, winHeight = 600;
static int window_id_main = 0;

void display() {
    static double angle = 0.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated(0.0, -1.0, -13.0);
    glRotated(angle, 0.0, 1.0, 0.0);
    angle += 0.25;
    glScalef(0.75, 0.75, 0.75);
    glTranslated(0.0, 0.0, 1.0);
    RenderQueue::getInstance()->render();
    glPopMatrix();
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void handle_special_keys(int key, int x, int y) {
}

void update_projection(GLsizei w, GLsizei h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w/(double)h, 0.1, 100);
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
    glutSpecialFunc(&handle_special_keys);
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
    return ret;
}

void init_opengl() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    update_projection(winWidth, winHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.75, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void load_viper() {
    std::ifstream viper_file("meshes/viper.obj");
    MeshLoader* loader = new WavefrontGLMeshLoader;
    Renderable* viper_model = loader->loadMesh(viper_file);
    RenderQueue::getInstance()->enqueue(*viper_model);
    delete loader;
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    const char *title = "Nebula Horizon";
    window_id_main = create_window(title, 40, 40, winWidth, winHeight);
    atexit(&exit_callback);
    create_callbacks();
    init_opengl();
    load_viper();
    glutMainLoop();
    return 0;
}
