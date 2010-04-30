#include <cstring>
#include <string>

#include "nhz_common.h"

// wglGetProcAddress function prototypes
#ifdef WIN32
PFNGLPOINTPARAMETERFVPROC NHZ_glPointParameterfvARB = NULL;
PFNGLCREATESHADERPROC NHZ_glCreateShader = NULL;
PFNGLATTACHSHADERPROC NHZ_glAttachShader = NULL;
PFNGLSHADERSOURCEPROC NHZ_glShaderSource = NULL;
PFNGLGETSHADERIVPROC NHZ_glGetShaderiv = NULL;
PFNGLCOMPILESHADERPROC NHZ_glCompileShader = NULL;
PFNGLDETACHSHADERPROC NHZ_glDetachShader = NULL;
PFNGLDELETESHADERPROC NHZ_glDeleteShader = NULL;
PFNGLGETSHADERINFOLOGPROC NHZ_glGetShaderInfoLog = NULL; 
PFNGLCREATEPROGRAMPROC NHZ_glCreateProgram = NULL;
PFNGLLINKPROGRAMPROC NHZ_glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC NHZ_glGetProgramiv = NULL;
PFNGLUSEPROGRAMPROC NHZ_glUseProgram = NULL;
PFNGLDELETEPROGRAMPROC NHZ_glDeleteProgram = NULL;
PFNGLGETPROGRAMINFOLOGPROC NHZ_glGetProgramInfoLog = NULL; 
PFNGLPROGRAMPARAMETERIEXTPROC NHZ_glProgramParameteri = NULL;
PFNGLGETATTRIBLOCATIONPROC NHZ_glGetAttribLocation = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC NHZ_glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC NHZ_glDisableVertexAttribArray = NULL;
PFNGLVERTEXATTRIBPOINTERPROC NHZ_glVertexAttribPointer = NULL;
PFNGLGENBUFFERSPROC NHZ_glGenBuffers = NULL;
PFNGLBINDBUFFERPROC NHZ_glBindBuffer = NULL;
PFNGLBUFFERDATAPROC NHZ_glBufferData = NULL;
#endif

static char *gl_extensions_supported = NULL;
static char _NHZ_ERR_STRING[NHZ_ERR_BUF_MAX];

#ifdef WIN32
static wchar_t _NHZ_ERR_WSTRING[NHZ_ERR_BUF_MAX];
#endif

int gl_has_extension(const char *extension) {
  int ret = 0;
  if(gl_extensions_supported == NULL) {
    gl_extensions_supported = (char *)glGetString(GL_EXTENSIONS);
  }
  ret = std::strstr(gl_extensions_supported, extension) != NULL;
  return ret;
}

int gl_supports_version(const double ver) {
  static double _gl_version_id = 0.0;
  if(_gl_version_id == 0.0) {
    _gl_version_id = atof((const char *)glGetString(GL_VERSION));
  }
  return ver <= _gl_version_id;
}

void gl_print_shader_infolog(GLuint shader) {
  int infologLength = 0;
  int charsWritten  = 0;
  char *infoLog;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

  if(infologLength > 0) {
    infoLog = (char *)malloc(infologLength);
    glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog); 
    NHZ_ERR("%s\n", infoLog);
    free(infoLog);
  }
}

void gl_print_program_infolog(GLuint program) {
  int infologLength = 0;
  int charsWritten  = 0;
  char *infoLog;

  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);

  if(infologLength > 0) {
    infoLog = (char *)malloc(infologLength);
    glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog); 
    NHZ_ERR("%s\n", infoLog);
    free(infoLog);
  }
}

char *_nhzgeterr() {
  return (char *)_NHZ_ERR_STRING;
}

#ifdef WIN32
wchar_t *_nhzgetwerr() {
  MultiByteToWideChar(CP_ACP, NULL, _nhzgeterr(), -1, _NHZ_ERR_WSTRING, 
                      NHZ_ERR_BUF_MAX);
  return (wchar_t *)_NHZ_ERR_WSTRING;
}
#endif

// wglGetProcAddress functions
#ifdef WIN32

#define NHZPROCLOAD(proctype, procname) \
  if ( NHZ_##procname == NULL ) { \
    NHZ_##procname = ( proctype )wglGetProcAddress( #procname ); \
    if ( NHZ_##procname == NULL ) { \
      NHZ_ERR( #procname " couldn't be loaded\n"); \
      NHZ_ERR("windows system error code %d\n", GetLastError()); \
    } \
  } else { \
    NHZ_ERR( #procname " already loaded\n" ); \
  }

#define IF_EXTENSION_IS_SUPPORTED(ext) \
  if(!gl_has_extension( ext )) { \
    NHZ_ERR( ext " is not supported; extension load aborted\n"); \
  } else \

#define IF_GL_VERSION_IS_SUPPORTED(ver, whatfor) \
  if(!gl_supports_version( ver )) { \
    NHZ_ERR("OpenGL version " #ver " not supported; ignoring " whatfor "\n"); \
  } else \

void nhz_load_all_gl_procs() {
  IF_EXTENSION_IS_SUPPORTED("GL_ARB_point_parameters") {
    NHZPROCLOAD(PFNGLPOINTPARAMETERFVARBPROC, glPointParameterfvARB);
  }
  IF_GL_VERSION_IS_SUPPORTED(2.0, "shaders") {
    NHZPROCLOAD(PFNGLCREATESHADERPROC, glCreateShader);
    NHZPROCLOAD(PFNGLATTACHSHADERPROC, glAttachShader);
    NHZPROCLOAD(PFNGLSHADERSOURCEPROC, glShaderSource);
    NHZPROCLOAD(PFNGLGETSHADERIVPROC, glGetShaderiv);
    NHZPROCLOAD(PFNGLCOMPILESHADERPROC, glCompileShader);
    NHZPROCLOAD(PFNGLDETACHSHADERPROC, glDetachShader);
    NHZPROCLOAD(PFNGLDELETESHADERPROC, glDeleteShader);
    NHZPROCLOAD(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog); 
  }
  IF_GL_VERSION_IS_SUPPORTED(2.0, "shader programs") {
    NHZPROCLOAD(PFNGLCREATEPROGRAMPROC, glCreateProgram);
    NHZPROCLOAD(PFNGLLINKPROGRAMPROC, glLinkProgram);
    NHZPROCLOAD(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
    NHZPROCLOAD(PFNGLUSEPROGRAMPROC, glUseProgram);
    NHZPROCLOAD(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
    NHZPROCLOAD(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog); 
    NHZPROCLOAD(PFNGLPROGRAMPARAMETERIEXTPROC, glProgramParameteri);
  }
  IF_GL_VERSION_IS_SUPPORTED(2.0, "shader attributes") {
    NHZPROCLOAD(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
    NHZPROCLOAD(PFNGLENABLEVERTEXATTRIBARRAYPROC,
                glEnableVertexAttribArray);
    NHZPROCLOAD(PFNGLDISABLEVERTEXATTRIBARRAYPROC,
                glDisableVertexAttribArray);
    NHZPROCLOAD(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
  }
  IF_GL_VERSION_IS_SUPPORTED(1.5, "buffer objects") {
    NHZPROCLOAD(PFNGLGENBUFFERSPROC, glGenBuffers);
    NHZPROCLOAD(PFNGLBINDBUFFERPROC, glBindBuffer);
    NHZPROCLOAD(PFNGLBUFFERDATAPROC, glBufferData);
  }
}

#undef IF_EXTENSION_IS_SUPPORTED
#undef NHZPROCLOAD
#endif
