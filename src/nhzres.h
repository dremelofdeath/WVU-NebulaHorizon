#ifndef NHZ_NHZRES_H
#define NHZ_NHZRES_H

#ifdef WIN32
#define NHZ_RES_T(base, file) "" base "\\" file
#else
#define NHZ_RES_T(base, file) file
#endif

#endif
