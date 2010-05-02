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
PFNGLGETUNIFORMLOCATIONPROC NHZ_glGetUniformLocation = NULL;
PFNGLGETUNIFORMFVPROC NHZ_glGetUniformfv = NULL;
PFNGLGETUNIFORMIVPROC NHZ_glGetUniformiv = NULL;
PFNGLGETACTIVEUNIFORMPROC NHZ_glGetActiveUniform = NULL;
PFNGLUNIFORM1FPROC NHZ_glUniform1f = NULL;
PFNGLUNIFORM2FPROC NHZ_glUniform2f = NULL;
PFNGLUNIFORM3FPROC NHZ_glUniform3f = NULL;
PFNGLUNIFORM4FPROC NHZ_glUniform4f = NULL;
PFNGLUNIFORM1IPROC NHZ_glUniform1i = NULL;
PFNGLUNIFORM2IPROC NHZ_glUniform2i = NULL;
PFNGLUNIFORM3IPROC NHZ_glUniform3i = NULL;
PFNGLUNIFORM4IPROC NHZ_glUniform4i = NULL;
PFNGLUNIFORM1FVPROC NHZ_glUniform1fv = NULL;
PFNGLUNIFORM2FVPROC NHZ_glUniform2fv = NULL;
PFNGLUNIFORM3FVPROC NHZ_glUniform3fv = NULL;
PFNGLUNIFORM4FVPROC NHZ_glUniform4fv = NULL;
PFNGLUNIFORM1IVPROC NHZ_glUniform1iv = NULL;
PFNGLUNIFORM2IVPROC NHZ_glUniform2iv = NULL;
PFNGLUNIFORM3IVPROC NHZ_glUniform3iv = NULL;
PFNGLUNIFORM4IVPROC NHZ_glUniform4iv = NULL;
PFNGLUNIFORMMATRIX2FVPROC NHZ_glUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX3FVPROC NHZ_glUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC NHZ_glUniformMatrix4fv = NULL;
PFNGLUNIFORMMATRIX2X3FVPROC NHZ_glUniformMatrix2x3fv = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC NHZ_glUniformMatrix3x2fv = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC NHZ_glUniformMatrix2x4fv = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC NHZ_glUniformMatrix4x2fv = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC NHZ_glUniformMatrix3x4fv = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC NHZ_glUniformMatrix4x3fv = NULL;
PFNGLGENBUFFERSPROC NHZ_glGenBuffers = NULL;
PFNGLBINDBUFFERPROC NHZ_glBindBuffer = NULL;
PFNGLBUFFERDATAPROC NHZ_glBufferData = NULL;
PFNGLISRENDERBUFFEREXTPROC NHZ_glIsRenderbufferEXT = NULL;
PFNGLBINDRENDERBUFFEREXTPROC NHZ_glBindRenderbufferEXT = NULL;
PFNGLDELETERENDERBUFFERSEXTPROC NHZ_glDeleteRenderbuffersEXT = NULL;
PFNGLGENRENDERBUFFERSEXTPROC NHZ_glGenRenderbuffersEXT = NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC NHZ_glRenderbufferStorageEXT = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC
                                     NHZ_glGetRenderbufferParameterivEXT = NULL;
PFNGLISFRAMEBUFFEREXTPROC NHZ_glIsFramebufferEXT = NULL;
PFNGLBINDFRAMEBUFFEREXTPROC NHZ_glBindFramebufferEXT = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC NHZ_glDeleteFramebuffersEXT = NULL;
PFNGLGENFRAMEBUFFERSEXTPROC NHZ_glGenFramebuffersEXT = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC NHZ_glCheckFramebufferStatusEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC NHZ_glFramebufferTexture1DEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC NHZ_glFramebufferTexture2DEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC NHZ_glFramebufferTexture3DEXT = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC NHZ_glFramebufferRenderbufferEXT = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC
                            NHZ_glGetFramebufferAttachmentParameterivEXT = NULL;
PFNGLGENERATEMIPMAPEXTPROC NHZ_glGenerateMipmapEXT = NULL;
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
  IF_GL_VERSION_IS_SUPPORTED(2.0, "shader uniforms") {
    NHZPROCLOAD(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
    NHZPROCLOAD(PFNGLGETUNIFORMFVPROC, glGetUniformfv);
    NHZPROCLOAD(PFNGLGETUNIFORMIVPROC, glGetUniformiv);
    NHZPROCLOAD(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform);
    NHZPROCLOAD(PFNGLUNIFORM1FPROC, glUniform1f);
    NHZPROCLOAD(PFNGLUNIFORM2FPROC, glUniform2f);
    NHZPROCLOAD(PFNGLUNIFORM3FPROC, glUniform3f);
    NHZPROCLOAD(PFNGLUNIFORM4FPROC, glUniform4f);
    NHZPROCLOAD(PFNGLUNIFORM1IPROC, glUniform1i);
    NHZPROCLOAD(PFNGLUNIFORM2IPROC, glUniform2i);
    NHZPROCLOAD(PFNGLUNIFORM3IPROC, glUniform3i);
    NHZPROCLOAD(PFNGLUNIFORM4IPROC, glUniform4i);
    NHZPROCLOAD(PFNGLUNIFORM1FVPROC, glUniform1fv);
    NHZPROCLOAD(PFNGLUNIFORM2FVPROC, glUniform2fv);
    NHZPROCLOAD(PFNGLUNIFORM3FVPROC, glUniform3fv);
    NHZPROCLOAD(PFNGLUNIFORM4FVPROC, glUniform4fv);
    NHZPROCLOAD(PFNGLUNIFORM1IVPROC, glUniform1iv);
    NHZPROCLOAD(PFNGLUNIFORM2IVPROC, glUniform2iv);
    NHZPROCLOAD(PFNGLUNIFORM3IVPROC, glUniform3iv);
    NHZPROCLOAD(PFNGLUNIFORM4IVPROC, glUniform4iv);
    NHZPROCLOAD(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);
    NHZPROCLOAD(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);
    NHZPROCLOAD(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
    NHZPROCLOAD(PFNGLUNIFORMMATRIX2X3FVPROC, glUniformMatrix2x3fv);
    NHZPROCLOAD(PFNGLUNIFORMMATRIX3X2FVPROC, glUniformMatrix3x2fv);
    NHZPROCLOAD(PFNGLUNIFORMMATRIX2X4FVPROC, glUniformMatrix2x4fv);
    NHZPROCLOAD(PFNGLUNIFORMMATRIX4X2FVPROC, glUniformMatrix4x2fv);
    NHZPROCLOAD(PFNGLUNIFORMMATRIX3X4FVPROC, glUniformMatrix3x4fv);
    NHZPROCLOAD(PFNGLUNIFORMMATRIX4X3FVPROC, glUniformMatrix4x3fv);
  }
  IF_GL_VERSION_IS_SUPPORTED(1.5, "buffer objects") {
    NHZPROCLOAD(PFNGLGENBUFFERSPROC, glGenBuffers);
    NHZPROCLOAD(PFNGLBINDBUFFERPROC, glBindBuffer);
    NHZPROCLOAD(PFNGLBUFFERDATAPROC, glBufferData);
  }
  IF_EXTENSION_IS_SUPPORTED("GL_EXT_framebuffer_object") {
    NHZPROCLOAD(PFNGLISRENDERBUFFEREXTPROC, glIsRenderbufferEXT);
    NHZPROCLOAD(PFNGLBINDRENDERBUFFEREXTPROC, glBindRenderbufferEXT);
    NHZPROCLOAD(PFNGLDELETERENDERBUFFERSEXTPROC, glDeleteRenderbuffersEXT);
    NHZPROCLOAD(PFNGLGENRENDERBUFFERSEXTPROC, glGenRenderbuffersEXT);
    NHZPROCLOAD(PFNGLRENDERBUFFERSTORAGEEXTPROC, glRenderbufferStorageEXT);
    NHZPROCLOAD(PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC,
                glGetRenderbufferParameterivEXT);
    NHZPROCLOAD(PFNGLISFRAMEBUFFEREXTPROC, glIsFramebufferEXT);
    NHZPROCLOAD(PFNGLBINDFRAMEBUFFEREXTPROC, glBindFramebufferEXT);
    NHZPROCLOAD(PFNGLDELETEFRAMEBUFFERSEXTPROC, glDeleteFramebuffersEXT);
    NHZPROCLOAD(PFNGLGENFRAMEBUFFERSEXTPROC, glGenFramebuffersEXT);
    NHZPROCLOAD(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC, glCheckFramebufferStatusEXT);
    NHZPROCLOAD(PFNGLFRAMEBUFFERTEXTURE1DEXTPROC, glFramebufferTexture1DEXT);
    NHZPROCLOAD(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC, glFramebufferTexture2DEXT);
    NHZPROCLOAD(PFNGLFRAMEBUFFERTEXTURE3DEXTPROC, glFramebufferTexture3DEXT);
    NHZPROCLOAD(PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC,
                glFramebufferRenderbufferEXT);
    NHZPROCLOAD(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC,
                glGetFramebufferAttachmentParameterivEXT);
    NHZPROCLOAD(PFNGLGENERATEMIPMAPEXTPROC, glGenerateMipmapEXT);
  }
}

#undef IF_EXTENSION_IS_SUPPORTED
#undef NHZPROCLOAD
#endif
