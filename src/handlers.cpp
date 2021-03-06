#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#include <atlbase.h>
#include <atlconv.h>
#include "../visualstudio/Nebula Horizon.h"
#define MAX_LOADSTRING 100
#endif

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include "handlers.h"
#include "RenderQueue.h"
#include "KeyboardManager.h"
#include "WavefrontGLMeshLoader.h"
#include "RenderQueue.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "Skycube.h"
#include "OceanPlane.h"
#include "nhz_common.h"

//static GLfloat light0_pos[4] = {-100.0f, -20.875f, 41.359375f, 0.0f};
static GLfloat light0_pos[4] = {0.0f, 0.0f, 0.0f, 1.0f};
static GLfloat light1_pos[4] = {-100.0f, -20.875f, 41.359375f, 0.0f};

static GLsizei winWidth = 800, winHeight = 600;
static int window_id_main = 0;

static double yangle = 0.0;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  //glTranslated(0.0, 0.0, -10.0);
  if(KeyboardManager::getInstance().isSpecialKeyDown(GLUT_KEY_UP)) {
    glTranslated(0.0, 0.0, 0.1);
  }
  if(KeyboardManager::getInstance().isSpecialKeyDown(GLUT_KEY_DOWN)) {
    glTranslated(0.0, 0.0, -0.1);
  }
  if(KeyboardManager::getInstance().isKeyDown('j')) {
    yangle += 0.3;
  }
  if(KeyboardManager::getInstance().isKeyDown('l')) {
    yangle -= 0.3;
  }
  if(KeyboardManager::getInstance().isKeyDown('i')) {
    glRotated(0.3, 1.0, 0.0, 0.0);
  }
  if(KeyboardManager::getInstance().isKeyDown('k')) {
    glRotated(-0.3, 1.0, 0.0, 0.0);
  }
  if(KeyboardManager::getInstance().isKeyDown('5')) {
    light0_pos[2] -= 0.05f;
  }
  if(KeyboardManager::getInstance().isKeyDown('8')) {
    light0_pos[2] += 0.05f;
  }
  if(KeyboardManager::getInstance().isKeyDown('4')) {
    light0_pos[0] -= 0.05f;
  }
  if(KeyboardManager::getInstance().isKeyDown('6')) {
    light0_pos[0] += 0.05f;
  }
  if(KeyboardManager::getInstance().isKeyDown('p')) {
    NHZ_ERR("%f, %f, %f\n", light0_pos[0], light0_pos[1], light0_pos[2]);
  }
  glRotated(yangle, 0.0, 1.0, 0.0);
  glPushMatrix();
  glTranslatef(-1.0f, 0.0f, 0.0f);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
  glPopMatrix();
  /*glPushMatrix();
  glDisable(GL_TEXTURE_2D);
  //glTranslated(10.00, 2.1875, -4.3359375);
  glColor3f(1.0f, 0.0f, 0.0f);
  glTranslatef(100.0f, 20.875, -41.359375f);
  glutSolidTeapot(10.0);
  glPopMatrix();(*/
  //glTranslated(0.0, 0.0, 10.0);
  // FIXME: delete this garbage
  glPushMatrix();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_TEXTURE_2D);
  static GLfloat _ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
  static GLfloat _diffuse[4] = {0.8f, 0.0f, 0.0f, 1.0f};
  static GLfloat _specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 48.9f);
  glTranslatef(2.0f, 1.0f, -4.2f);
  glutSolidTeapot(1.0);
  glPopAttrib();
  glPopMatrix();
  RenderQueue::getInstance()->render();
  glutSwapBuffers();
}

#ifdef WIN32
static HINSTANCE hInstance = NULL;
static HHOOK nextHook;

void win32_set_hInstance(HINSTANCE inst) {
  hInstance = inst;
}

HINSTANCE win32_get_hInstance() {
  return hInstance;
}

void win32_idle_handle_messages() {
  static HACCEL hAccelTable = NULL;
  MSG msg;
  if(!hAccelTable && !win32_get_hInstance()) {
    hAccelTable = LoadAccelerators(win32_get_hInstance(),
                                   MAKEINTRESOURCE(IDC_NEBULAHORIZON));
  }
  if(hAccelTable) {
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
  }
}

LRESULT CALLBACK CallWndProc(int code, WPARAM wParam, LPARAM lParam) {
  if(code < 0) {
    return CallNextHookEx(nextHook, code, wParam, lParam);
  }
  switch(code) {
    case HC_ACTION:
      PCWPSTRUCT cwp = (PCWPSTRUCT)lParam;
      switch(cwp->message) {
        case WM_MOVING:
        case WM_GETICON:
        case WM_MOVE:
          idle();
          RedrawWindow(cwp->hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
          break;
      }
      break;
  }
  return CallNextHookEx(nextHook, code, wParam, lParam);
}
#endif

void idle() {
  static int last_time = 0;
  int time = glutGet(GLUT_ELAPSED_TIME);
  // if we overflow, last_time will be greater than time
  int elapsed = last_time <= time ? time-last_time : time+last_time;
  last_time = time;
  RenderQueue::getInstance()->idle(elapsed);
#ifdef WIN32
  win32_idle_handle_messages();
#endif
  glutPostRedisplay();
}

void handle_keyboard(unsigned char key, int x, int y) {
  KeyboardManager::getInstance().updateKeyState(key, true);
}

void handle_keyboard_up(unsigned char key, int x, int y) {
  KeyboardManager::getInstance().updateKeyState(key, false);
}

void handle_special_key(int key, int x, int y) {
  KeyboardManager::getInstance().updateSpecialKeyState(key, true);
}

void handle_special_key_up(int key, int x, int y) {
  KeyboardManager::getInstance().updateSpecialKeyState(key, false);
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
  glutSpecialUpFunc(&handle_special_key_up);
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
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  return ret;
}

void init_opengl() {
  static const GLfloat ambient0[4] = {0.1f, 0.1f, 0.1f, 1.0f};
  static const GLfloat diffuse0[4] = {0.7f, 0.7f, 0.69f, 1.0f};
  static const GLfloat specular0[4] = {1.0f, 1.0f, 0.94f, 1.0f};
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  update_projection(winWidth, winHeight);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
  // FIXME: this light1 crap is crap
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);
  //gluLookAt(0.0, 0.0, -2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void set_window_id(int id) {
  window_id_main = id;
}

void main_springload() {
#ifdef WIN32
  TCHAR szTitle[MAX_LOADSTRING];
  USES_CONVERSION;
  LoadString(win32_get_hInstance(), IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  const char *title = T2A(szTitle);
#else
  const char *title = "Nebula Horizon";
#endif
  set_window_id(create_window(title, 40, 40, 800, 600));
  atexit(&exit_callback);
  create_callbacks();
#ifdef WIN32
  nextHook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc,
                              GetModuleHandle(NULL), GetCurrentThreadId());
  nhz_load_all_gl_procs();
#endif
  init_opengl();
  ilInit();
  iluInit();
  ilutInit();
  ilutRenderer(ILUT_OPENGL);
  Player player(5.0f, 5.0f);
  //EnemySpawner spawner(&player);
  RenderQueue::getInstance()->enqueue(player);
  //RenderQueue::getInstance()->enqueue(spawner);
  Skycube skycube(NHZ_RES_T("textures", "north.png"),
                  NHZ_RES_T("textures", "south.png"),
                  NHZ_RES_T("textures", "east.png"),
                  NHZ_RES_T("textures", "west.png"),
                  NHZ_RES_T("textures", "up.png"),
                  NHZ_RES_T("textures", "down.png"));
  RenderQueue::getInstance()->enqueue(skycube);
  OceanPlane ocean;
  RenderQueue::getInstance()->enqueue(ocean);
  glutMainLoop();
}
