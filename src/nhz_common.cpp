#include "nhz_common.h"

static char _NHZ_ERR_STRING[NHZ_ERR_BUF_MAX];

#ifdef WIN32
static wchar_t _NHZ_ERR_WSTRING[NHZ_ERR_BUF_MAX];
#endif

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
