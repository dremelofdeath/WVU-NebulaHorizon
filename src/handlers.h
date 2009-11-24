/*
 *  handlers.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/24/09.
 *
 */

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifndef NHZ_HANDLERS_H
#define NHZ_HANDLERS_H

#ifdef __cplusplus
extern "C" {
#endif

void display();
void idle();
void handle_keyboard(unsigned char key, int x, int y);
void handle_special_key(int key, int x, int y);
void handle_mouse_event(int button, int state, int x, int y);
void handle_mouse_drag(int x, int y);
void handle_mouse_motion(int x, int y);
void update_projection(GLsizei w, GLsizei h);
static void reshape(GLsizei w, GLsizei h);
void create_callbacks();
void exit_callback();
int create_window(const char *title, int xpos, int ypos, int ww, int wh);
void init_opengl();
void load_viper();
void set_window_id(int id);

#ifdef __cplusplus
}
#endif

#endif
