#ifndef NHZ_NHZ_COMMON_H
#define NHZ_NHZ_COMMON_H

#include <stdio.h>

#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define NHZ_ERR_BUF_MAX 256

char *_nhzgeterr();

#ifdef WIN32
wchar_t *_nhzgetwerr();
#endif

#define _NHZERRFMT "" __FILE__ ", line %d: ", __LINE__

#ifdef WIN32
#define NHZ_RES_T(base, file) "" base "\\" file
#define NHZ_ERR(...) sprintf_s(_nhzgeterr(), NHZ_ERR_BUF_MAX, _NHZERRFMT);\
  OutputDebugString(_nhzgetwerr()); \
  sprintf_s(_nhzgeterr(), NHZ_ERR_BUF_MAX, __VA_ARGS__); \
  OutputDebugString(_nhzgetwerr())
#else
#define NHZ_RES_T(base, file) file
#define NHZ_ERR(...) fprintf(stderr, _NHZERRFMT); \
  sprintf(_nhzgeterr(), __VA_ARGS__); \
  fprintf(stderr, _nhzgeterr());
#endif

#ifdef __cplusplus
}
#endif

#endif
