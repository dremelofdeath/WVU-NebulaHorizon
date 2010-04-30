#ifndef NHZ_NHZ_COMMON_H
#define NHZ_NHZ_COMMON_H

#include <stdio.h>

#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif // #ifndef WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // #ifdef WIN32

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#ifdef WIN32
#include <GL/wglext.h>
#endif // #ifdef WIN32
#endif // #ifdef __APPLE__

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#define NHZ_ERR_BUF_MAX 256

int gl_has_extension(const char *extension);
int gl_supports_version(const double ver);
void gl_print_shader_infolog(GLuint shader);
void gl_print_program_infolog(GLuint program);
char *_nhzgeterr();

#ifdef WIN32
wchar_t *_nhzgetwerr();
void nhz_load_all_gl_procs();
#endif // #ifdef WIN32

// below contains the error and resource macros
#define _NHZERRFMT "" __FILE__ ", line %d: ", __LINE__

#ifdef WIN32
#define NHZ_RES_T(base, file) "" base "\\" file
#define NHZ_ERR(...) { \
    sprintf_s(_nhzgeterr(), NHZ_ERR_BUF_MAX, _NHZERRFMT ); \
    OutputDebugString(_nhzgetwerr()); \
    sprintf_s(_nhzgeterr(), NHZ_ERR_BUF_MAX, __VA_ARGS__ ); \
    OutputDebugString(_nhzgetwerr()); \
  }
#else
#define NHZ_RES_T(base, file) file
#define NHZ_ERR(...) { \
    fprintf(stderr, _NHZERRFMT ); \
    sprintf(_nhzgeterr(), __VA_ARGS__ ); \
    fprintf(stderr, _nhzgeterr()); \
  }
#endif // #ifdef WIN32

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

// extensions loading for Windows because it's not done for you
#ifdef WIN32

// HEADS UP! If you want to disable NHZ's CUSTOM shader compile autologger, then
// comment out the following line! Keep in mind the autologger will still only
// print the log when _DEBUG is defined. (This says COMPILE but it works for
// linking too!) --zack <3
// FIXME: this currently only works when compiling for Windows. maybe an #else
// and another macro will fix this? NHZAUTOLOG should work on all platforms
#define NHZ_USING_CUSTOM_COMPILE_AUTOLOGGER 1

#define _NHZPROCCOMPLAIN(glfunc) \
  NHZ_ERR("trapped a stray call to " #glfunc " while it was NULL\n");

// only check if we're targeting a debug build
#ifdef _DEBUG
#define _NHZCHECKANDCALL(glfunc, ...) \
  if ( NHZ_##glfunc == NULL ) { \
    _NHZPROCCOMPLAIN(glfunc); \
  } else NHZ_##glfunc##( __VA_ARGS__ )
#else
// save a little time by not checking nullness for every glext call
#define _NHZCHECKANDCALL(glfunc, ...) \
  NHZ_##glfunc##( __VA_ARGS__ )
#endif // #ifdef _DEBUG

// nhz autologger definition
#ifdef NHZ_USING_CUSTOM_COMPILE_AUTOLOGGER
// example usage (with shader a GLuint): NHZAUTOLOG(Shader, shader);
#define NHZAUTOLOG(op_type, gluint_obj) { \
  int infologLength = 0; \
  int chars = 0; \
  char *infoLog; \
  glGet##op_type##iv(gluint_obj, GL_INFO_LOG_LENGTH, &infologLength); \
  if(infologLength > 0) { \
    infoLog = (char *)malloc(infologLength); \
    glGet##op_type##InfoLog(gluint_obj, infologLength, &chars, infoLog); \
    NHZ_ERR(#op_type " operation failed: %s\n", infoLog); \
    free(infoLog); \
  } else { \
    NHZ_ERR(#op_type " operation failed, but no infolog was generated\n"); \
  } \
}
#endif

// windows gl extension prototypes go here (follow the pattern)

// Additional geometric characteristics of points
// Requires: OpenGL 1.0, extension GL_ARB_point_parameters
extern PFNGLPOINTPARAMETERFVARBPROC NHZ_glPointParameterfvARB;
#define glPointParameterfvARB(...) \
  _NHZCHECKANDCALL(glPointParameterfvARB, __VA_ARGS__ );

// Shader creation and compilation
// Requires: OpenGL 2.0
extern PFNGLCREATESHADERPROC NHZ_glCreateShader;
#define glCreateShader(...) \
  _NHZCHECKANDCALL(glCreateShader, __VA_ARGS__ );
extern PFNGLATTACHSHADERPROC NHZ_glAttachShader;
#define glAttachShader(...) \
  _NHZCHECKANDCALL(glAttachShader, __VA_ARGS__ );
extern PFNGLSHADERSOURCEPROC NHZ_glShaderSource;
#define glShaderSource(...) \
  _NHZCHECKANDCALL(glShaderSource, __VA_ARGS__ );
extern PFNGLGETSHADERIVPROC NHZ_glGetShaderiv;
#define glGetShaderiv(...) \
  _NHZCHECKANDCALL(glGetShaderiv, __VA_ARGS__ );
extern PFNGLCOMPILESHADERPROC NHZ_glCompileShader;
#if defined(_DEBUG) && defined(NHZ_USING_CUSTOM_COMPILE_AUTOLOGGER)
#define glCompileShader(...) { \
  int _nhzcompilestatus = 0; \
  _NHZCHECKANDCALL(glCompileShader, __VA_ARGS__); \
  glGetShaderiv( __VA_ARGS__ , GL_COMPILE_STATUS, &_nhzcompilestatus); \
  if(_nhzcompilestatus == GL_FALSE) { \
    NHZAUTOLOG(Shader, __VA_ARGS__ ); \
  } \
}
#else
#define glCompileShader(...) \
  _NHZCHECKANDCALL(glCompileShader, __VA_ARGS__ );
#endif // #if defined(_DEBUG) && defined(NHZ_USING_CUSTOM_COMPILE_AUTOLOGGER)
extern PFNGLDETACHSHADERPROC NHZ_glDetachShader;
#define glDetachShader(...) \
  _NHZCHECKANDCALL(glDetachShader, __VA_ARGS__ );
extern PFNGLDELETESHADERPROC NHZ_glDeleteShader;
#define glDeleteShader(...) \
  _NHZCHECKANDCALL(glDeleteShader, __VA_ARGS__ );
extern PFNGLGETSHADERINFOLOGPROC NHZ_glGetShaderInfoLog; 
#define glGetShaderInfoLog(...) \
  _NHZCHECKANDCALL(glGetShaderInfoLog, __VA_ARGS__ );

// Program linking and usage
// Requires OpenGL 2.0
extern PFNGLCREATEPROGRAMPROC NHZ_glCreateProgram;
#define glCreateProgram(...) \
  _NHZCHECKANDCALL(glCreateProgram, __VA_ARGS__ );
extern PFNGLLINKPROGRAMPROC NHZ_glLinkProgram;
#if defined(_DEBUG) && defined(NHZ_USING_CUSTOM_COMPILE_AUTOLOGGER)
#define glLinkProgram(...) { \
  int _nhzlinkstatus = 0; \
  _NHZCHECKANDCALL(glLinkProgram, __VA_ARGS__); \
  glGetProgramiv( __VA_ARGS__ , GL_LINK_STATUS, &_nhzlinkstatus); \
  if(_nhzlinkstatus == GL_FALSE) { \
    NHZAUTOLOG(Program, __VA_ARGS__ ); \
  } \
}
#else
#define glLinkProgram(...) \
  _NHZCHECKANDCALL(glLinkProgram, __VA_ARGS__ );
#endif
extern PFNGLGETPROGRAMIVPROC NHZ_glGetProgramiv;
#define glGetProgramiv(...) \
  _NHZCHECKANDCALL(glGetProgramiv, __VA_ARGS__ );
extern PFNGLUSEPROGRAMPROC NHZ_glUseProgram;
#define glUseProgram(...) \
  _NHZCHECKANDCALL(glUseProgram, __VA_ARGS__ );
extern PFNGLDELETEPROGRAMPROC NHZ_glDeleteProgram;
#define glDeleteProgram(...) \
  _NHZCHECKANDCALL(glDeleteProgram, __VA_ARGS__ );
extern PFNGLGETPROGRAMINFOLOGPROC NHZ_glGetProgramInfoLog; 
#define glGetProgramInfoLog(...) \
  _NHZCHECKANDCALL(glGetProgramInfoLog, __VA_ARGS__ );
extern PFNGLPROGRAMPARAMETERIEXTPROC NHZ_glProgramParameteri;
#define glProgramParameteri(...) \
  _NHZCHECKANDCALL(glProgramParameteri, __VA_ARGS__ );

// Shader attributes
// Requires: OpenGL 2.0
extern PFNGLGETATTRIBLOCATIONPROC NHZ_glGetAttribLocation;
#define glGetAttribLocation(...) \
  _NHZCHECKANDCALL(glGetAttribLocation, __VA_ARGS__ );
extern PFNGLENABLEVERTEXATTRIBARRAYPROC NHZ_glEnableVertexAttribArray;
#define glEnableVertexAttribArray(...) \
  _NHZCHECKANDCALL(glEnableVertexAttribArray, __VA_ARGS__ );
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC NHZ_glDisableVertexAttribArray;
#define glDisableVertexAttribArray(...) \
  _NHZCHECKANDCALL(glDisableVertexAttribArray, __VA_ARGS__ );
extern PFNGLVERTEXATTRIBPOINTERPROC NHZ_glVertexAttribPointer;
#define glVertexAttribPointer(...) \
  _NHZCHECKANDCALL(glVertexAttribPointer, __VA_ARGS__ );

// Buffer objects
// Requires: OpenGL 1.5
extern PFNGLGENBUFFERSPROC NHZ_glGenBuffers;
#define glGenBuffers(...) \
  _NHZCHECKANDCALL(glGenBuffers, __VA_ARGS__ );
extern PFNGLBINDBUFFERPROC NHZ_glBindBuffer;
#define glBindBuffer(...) \
  _NHZCHECKANDCALL(glBindBuffer, __VA_ARGS__ );
extern PFNGLBUFFERDATAPROC NHZ_glBufferData;
#define glBufferData(...) \
  _NHZCHECKANDCALL(glBufferData, __VA_ARGS__ );

#endif // #ifdef WIN32

#endif // #ifndef NHZ_NHZ_COMMON_H
