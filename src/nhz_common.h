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

#define NHZ_ERR_BUF_MAX 4096

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
// OH MY GOD, LOOK! Those are commas, not semicolons! DEAR LORD IN HEAVEN!
// Why, might you ask, instead of a block with semicolons? Well, what if you
// want to use NHZ_ERR in the middle of a ternary if expression? Well, huh?
#define NHZ_ERR(...) \
  sprintf_s(_nhzgeterr(), NHZ_ERR_BUF_MAX, _NHZERRFMT ), \
  OutputDebugString(_nhzgetwerr()), \
  sprintf_s(_nhzgeterr(), NHZ_ERR_BUF_MAX, __VA_ARGS__ ), \
  OutputDebugString(_nhzgetwerr()), NULL
#else
#define NHZ_RES_T(base, file) file
#define NHZ_ERR(...) \
    fprintf(stderr, _NHZERRFMT ), \
    sprintf(_nhzgeterr(), __VA_ARGS__ ), \
    fprintf(stderr, _nhzgeterr()), NULL
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
  NHZ_ERR("trapped a stray call to " #glfunc " while it was NULL\n")

// only check if we're targeting a debug build
#ifdef _DEBUG
/*#define _NHZCHECKANDCALL(glfunc, ...) \
  if ( NHZ_##glfunc == NULL ) { \
    _NHZPROCCOMPLAIN(glfunc); \
  } else NHZ_##glfunc##( __VA_ARGS__ )*/
#define _NHZCHECKANDCALL(glfunc, ...) \
  NHZ_##glfunc == NULL ? \
    _NHZPROCCOMPLAIN(glfunc), NULL : NHZ_##glfunc##( __VA_ARGS__ )
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
    NHZ_ERR(#op_type " operation failed.\n%s\n", infoLog); \
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
  _NHZCHECKANDCALL(glPointParameterfvARB, __VA_ARGS__ )

// Shader creation and compilation
// Requires: OpenGL 2.0
extern PFNGLCREATESHADERPROC NHZ_glCreateShader;
#define glCreateShader(...) \
  _NHZCHECKANDCALL(glCreateShader, __VA_ARGS__ )
extern PFNGLATTACHSHADERPROC NHZ_glAttachShader;
#define glAttachShader(...) \
  _NHZCHECKANDCALL(glAttachShader, __VA_ARGS__ )
extern PFNGLSHADERSOURCEPROC NHZ_glShaderSource;
#define glShaderSource(...) \
  _NHZCHECKANDCALL(glShaderSource, __VA_ARGS__ )
extern PFNGLGETSHADERIVPROC NHZ_glGetShaderiv;
#define glGetShaderiv(...) \
  _NHZCHECKANDCALL(glGetShaderiv, __VA_ARGS__ )
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
  _NHZCHECKANDCALL(glCompileShader, __VA_ARGS__ )
#endif // #if defined(_DEBUG) && defined(NHZ_USING_CUSTOM_COMPILE_AUTOLOGGER)
extern PFNGLDETACHSHADERPROC NHZ_glDetachShader;
#define glDetachShader(...) \
  _NHZCHECKANDCALL(glDetachShader, __VA_ARGS__ )
extern PFNGLDELETESHADERPROC NHZ_glDeleteShader;
#define glDeleteShader(...) \
  _NHZCHECKANDCALL(glDeleteShader, __VA_ARGS__ )
extern PFNGLGETSHADERINFOLOGPROC NHZ_glGetShaderInfoLog; 
#define glGetShaderInfoLog(...) \
  _NHZCHECKANDCALL(glGetShaderInfoLog, __VA_ARGS__ )

// Program linking and usage
// Requires OpenGL 2.0
extern PFNGLCREATEPROGRAMPROC NHZ_glCreateProgram;
#define glCreateProgram(...) \
  _NHZCHECKANDCALL(glCreateProgram, __VA_ARGS__ )
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
  _NHZCHECKANDCALL(glLinkProgram, __VA_ARGS__ )
#endif
extern PFNGLGETPROGRAMIVPROC NHZ_glGetProgramiv;
#define glGetProgramiv(...) \
  _NHZCHECKANDCALL(glGetProgramiv, __VA_ARGS__ )
extern PFNGLUSEPROGRAMPROC NHZ_glUseProgram;
#define glUseProgram(...) \
  _NHZCHECKANDCALL(glUseProgram, __VA_ARGS__ )
extern PFNGLDELETEPROGRAMPROC NHZ_glDeleteProgram;
#define glDeleteProgram(...) \
  _NHZCHECKANDCALL(glDeleteProgram, __VA_ARGS__ )
extern PFNGLGETPROGRAMINFOLOGPROC NHZ_glGetProgramInfoLog; 
#define glGetProgramInfoLog(...) \
  _NHZCHECKANDCALL(glGetProgramInfoLog, __VA_ARGS__ )
extern PFNGLPROGRAMPARAMETERIEXTPROC NHZ_glProgramParameteri;
#define glProgramParameteri(...) \
  _NHZCHECKANDCALL(glProgramParameteri, __VA_ARGS__ )

// Shader attributes
// Requires: OpenGL 2.0
extern PFNGLGETATTRIBLOCATIONPROC NHZ_glGetAttribLocation;
#define glGetAttribLocation(...) \
  _NHZCHECKANDCALL(glGetAttribLocation, __VA_ARGS__ )
extern PFNGLENABLEVERTEXATTRIBARRAYPROC NHZ_glEnableVertexAttribArray;
#define glEnableVertexAttribArray(...) \
  _NHZCHECKANDCALL(glEnableVertexAttribArray, __VA_ARGS__ )
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC NHZ_glDisableVertexAttribArray;
#define glDisableVertexAttribArray(...) \
  _NHZCHECKANDCALL(glDisableVertexAttribArray, __VA_ARGS__ )
extern PFNGLVERTEXATTRIBPOINTERPROC NHZ_glVertexAttribPointer;
#define glVertexAttribPointer(...) \
  _NHZCHECKANDCALL(glVertexAttribPointer, __VA_ARGS__ )

// Shader uniforms
// Requires: OpenGL 2.0
extern PFNGLGETUNIFORMLOCATIONPROC NHZ_glGetUniformLocation;
#define glGetUniformLocation(...) \
  _NHZCHECKANDCALL(glGetUniformLocation, __VA_ARGS__ )
extern PFNGLGETUNIFORMFVPROC NHZ_glGetUniformfv;
#define glGetUniformfv(...) \
  _NHZCHECKANDCALL(glGetUniformfv, __VA_ARGS__ )
extern PFNGLGETUNIFORMIVPROC NHZ_glGetUniformiv;
#define glGetUniformiv(...) \
  _NHZCHECKANDCALL(glGetUniformiv, __VA_ARGS__ )
extern PFNGLGETACTIVEUNIFORMPROC NHZ_glGetActiveUniform;
#define glGetActiveUniform(...) \
  _NHZCHECKANDCALL(glGetActiveUniform, __VA_ARGS__ )
extern PFNGLUNIFORM1FPROC NHZ_glUniform1f;
#define glUniform1f(...) \
  _NHZCHECKANDCALL(glUniform1f, __VA_ARGS__ )
extern PFNGLUNIFORM2FPROC NHZ_glUniform2f;
#define glUniform2f(...) \
  _NHZCHECKANDCALL(glUniform2f, __VA_ARGS__ )
extern PFNGLUNIFORM3FPROC NHZ_glUniform3f;
#define glUniform3f(...) \
  _NHZCHECKANDCALL(glUniform3f, __VA_ARGS__ )
extern PFNGLUNIFORM4FPROC NHZ_glUniform4f;
#define glUniform4f(...) \
  _NHZCHECKANDCALL(glUniform4f, __VA_ARGS__ )
extern PFNGLUNIFORM1IPROC NHZ_glUniform1i;
#define glUniform1i(...) \
  _NHZCHECKANDCALL(glUniform1i, __VA_ARGS__ )
extern PFNGLUNIFORM2IPROC NHZ_glUniform2i;
#define glUniform2i(...) \
  _NHZCHECKANDCALL(glUniform2i, __VA_ARGS__ )
extern PFNGLUNIFORM3IPROC NHZ_glUniform3i;
#define glUniform3i(...) \
  _NHZCHECKANDCALL(glUniform3i, __VA_ARGS__ )
extern PFNGLUNIFORM4IPROC NHZ_glUniform4i;
#define glUniform4i(...) \
  _NHZCHECKANDCALL(glUniform4i, __VA_ARGS__ )
extern PFNGLUNIFORM1FVPROC NHZ_glUniform1fv;
#define glUniform1fv(...) \
  _NHZCHECKANDCALL(glUniform1fv, __VA_ARGS__ )
extern PFNGLUNIFORM2FVPROC NHZ_glUniform2fv;
#define glUniform2fv(...) \
  _NHZCHECKANDCALL(glUniform2fv, __VA_ARGS__ )
extern PFNGLUNIFORM3FVPROC NHZ_glUniform3fv;
#define glUniform3fv(...) \
  _NHZCHECKANDCALL(glUniform3fv, __VA_ARGS__ )
extern PFNGLUNIFORM4FVPROC NHZ_glUniform4fv;
#define glUniform4fv(...) \
  _NHZCHECKANDCALL(glUniform4fv, __VA_ARGS__ )
extern PFNGLUNIFORM1IVPROC NHZ_glUniform1iv;
#define glUniform1iv(...) \
  _NHZCHECKANDCALL(glUniform1iv, __VA_ARGS__ )
extern PFNGLUNIFORM2IVPROC NHZ_glUniform2iv;
#define glUniform2iv(...) \
  _NHZCHECKANDCALL(glUniform2iv, __VA_ARGS__ )
extern PFNGLUNIFORM3IVPROC NHZ_glUniform3iv;
#define glUniform3iv(...) \
  _NHZCHECKANDCALL(glUniform3iv, __VA_ARGS__ )
extern PFNGLUNIFORM4IVPROC NHZ_glUniform4iv;
#define glUniform4iv(...) \
  _NHZCHECKANDCALL(glUniform4iv, __VA_ARGS__ )
extern PFNGLUNIFORMMATRIX2FVPROC NHZ_glUniformMatrix2fv;
#define glUniformMatrix2fv(...) \
  _NHZCHECKANDCALL(glUniformMatrix2fv, __VA_ARGS__ )
extern PFNGLUNIFORMMATRIX3FVPROC NHZ_glUniformMatrix3fv;
#define glUniformMatrix3fv(...) \
  _NHZCHECKANDCALL(glUniformMatrix3fv, __VA_ARGS__ )
extern PFNGLUNIFORMMATRIX4FVPROC NHZ_glUniformMatrix4fv;
#define glUniformMatrix4fv(...) \
  _NHZCHECKANDCALL(glUniformMatrix4fv, __VA_ARGS__ )
extern PFNGLUNIFORMMATRIX2X3FVPROC NHZ_glUniformMatrix2x3fv;
#define glUniformMatrix2x3fv(...) \
  _NHZCHECKANDCALL(glUniformMatrix2x3fv, __VA_ARGS__ )
extern PFNGLUNIFORMMATRIX3X2FVPROC NHZ_glUniformMatrix3x2fv;
#define glUniformMatrix3x2fv(...) \
  _NHZCHECKANDCALL(glUniformMatrix3x2fv, __VA_ARGS__ )
extern PFNGLUNIFORMMATRIX2X4FVPROC NHZ_glUniformMatrix2x4fv;
#define glUniformMatrix2x4fv(...) \
  _NHZCHECKANDCALL(glUniformMatrix2x4fv, __VA_ARGS__ )
extern PFNGLUNIFORMMATRIX4X2FVPROC NHZ_glUniformMatrix4x2fv;
#define glUniformMatrix4x2fv(...) \
  _NHZCHECKANDCALL(glUniformMatrix4x2fv, __VA_ARGS__ )
extern PFNGLUNIFORMMATRIX3X4FVPROC NHZ_glUniformMatrix3x4fv;
#define glUniformMatrix3x4fv(...) \
  _NHZCHECKANDCALL(glUniformMatrix3x4fv, __VA_ARGS__ )
extern PFNGLUNIFORMMATRIX4X3FVPROC NHZ_glUniformMatrix4x3fv;
#define glUniformMatrix4x3fv(...) \
  _NHZCHECKANDCALL(glUniformMatrix4x3fv, __VA_ARGS__ )

// Buffer objects
// Requires: OpenGL 1.5
extern PFNGLGENBUFFERSPROC NHZ_glGenBuffers;
#define glGenBuffers(...) \
  _NHZCHECKANDCALL(glGenBuffers, __VA_ARGS__ )
extern PFNGLBINDBUFFERPROC NHZ_glBindBuffer;
#define glBindBuffer(...) \
  _NHZCHECKANDCALL(glBindBuffer, __VA_ARGS__ )
extern PFNGLBUFFERDATAPROC NHZ_glBufferData;
#define glBufferData(...) \
  _NHZCHECKANDCALL(glBufferData, __VA_ARGS__ )

// Framebuffer objects and Renderbuffers
// Requires: OpenGL 1.1, extension GL_EXT_framebuffer_object
extern PFNGLISRENDERBUFFEREXTPROC NHZ_glIsRenderbufferEXT;
#define glIsRenderbufferEXT(...) \
  _NHZCHECKANDCALL(glIsRenderbufferEXT, __VA_ARGS__ )
extern PFNGLBINDRENDERBUFFEREXTPROC NHZ_glBindRenderbufferEXT;
#define glBindRenderbufferEXT(...) \
  _NHZCHECKANDCALL(glBindRenderbufferEXT, __VA_ARGS__ )
extern PFNGLDELETERENDERBUFFERSEXTPROC NHZ_glDeleteRenderbuffersEXT;
#define glDeleteRenderbuffersEXT(...) \
  _NHZCHECKANDCALL(glDeleteRenderbuffersEXT, __VA_ARGS__ )
extern PFNGLGENRENDERBUFFERSEXTPROC NHZ_glGenRenderbuffersEXT;
#define glGenRenderbuffersEXT(...) \
  _NHZCHECKANDCALL(glGenRenderbuffersEXT, __VA_ARGS__ )
extern PFNGLRENDERBUFFERSTORAGEEXTPROC NHZ_glRenderbufferStorageEXT;
#define glRenderbufferStorageEXT(...) \
  _NHZCHECKANDCALL(glRenderbufferStorageEXT, __VA_ARGS__ )
extern PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC
                                           NHZ_glGetRenderbufferParameterivEXT;
#define glGetRenderbufferParameterivEXT(...) \
  _NHZCHECKANDCALL(glGetRenderbufferParameterivEXT, __VA_ARGS__ )
extern PFNGLISFRAMEBUFFEREXTPROC NHZ_glIsFramebufferEXT;
#define glIsFramebufferEXT(...) \
  _NHZCHECKANDCALL(glIsFramebufferEXT, __VA_ARGS__ )
extern PFNGLBINDFRAMEBUFFEREXTPROC NHZ_glBindFramebufferEXT;
#define glBindFramebufferEXT(...) \
  _NHZCHECKANDCALL(glBindFramebufferEXT, __VA_ARGS__ )
extern PFNGLDELETEFRAMEBUFFERSEXTPROC NHZ_glDeleteFramebuffersEXT;
#define glDeleteFramebuffersEXT(...) \
  _NHZCHECKANDCALL(glDeleteFramebuffersEXT, __VA_ARGS__ )
extern PFNGLGENFRAMEBUFFERSEXTPROC NHZ_glGenFramebuffersEXT;
#define glGenFramebuffersEXT(...) \
  _NHZCHECKANDCALL(glGenFramebuffersEXT, __VA_ARGS__ )
extern PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC NHZ_glCheckFramebufferStatusEXT;
#define glCheckFramebufferStatusEXT(...) \
  _NHZCHECKANDCALL(glCheckFramebufferStatusEXT, __VA_ARGS__ )
extern PFNGLFRAMEBUFFERTEXTURE1DEXTPROC NHZ_glFramebufferTexture1DEXT;
#define glFramebufferTexture1DEXT(...) \
  _NHZCHECKANDCALL(glFramebufferTexture1DEXT, __VA_ARGS__ )
extern PFNGLFRAMEBUFFERTEXTURE2DEXTPROC NHZ_glFramebufferTexture2DEXT;
#define glFramebufferTexture2DEXT(...) \
  _NHZCHECKANDCALL(glFramebufferTexture2DEXT, __VA_ARGS__ )
extern PFNGLFRAMEBUFFERTEXTURE3DEXTPROC NHZ_glFramebufferTexture3DEXT;
#define glFramebufferTexture3DEXT(...) \
  _NHZCHECKANDCALL(glFramebufferTexture3DEXT, __VA_ARGS__ )
extern PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC NHZ_glFramebufferRenderbufferEXT;
#define glFramebufferRenderbufferEXT(...) \
  _NHZCHECKANDCALL(glFramebufferRenderbufferEXT, __VA_ARGS__ )
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC
                                   NHZ_glGetFramebufferAttachmentParameterivEXT;
#define glGetFramebufferAttachmentParameterivEXT(...) \
  _NHZCHECKANDCALL(glGetFramebufferAttachmentParameterivEXT, __VA_ARGS__ )
extern PFNGLGENERATEMIPMAPEXTPROC NHZ_glGenerateMipmapEXT;
#define glGenerateMipmapEXT(...) \
  _NHZCHECKANDCALL(glGenerateMipmapEXT, __VA_ARGS__ )

#endif // #ifdef WIN32

#endif // #ifndef NHZ_NHZ_COMMON_H
