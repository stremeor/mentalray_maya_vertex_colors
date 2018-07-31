//
//  vertexcolors.h
//  mr custom shader
//
//  Provided "as is".
//

#ifndef vertexcolors_h
#define vertexcolors_h

#include <stdio.h>

/* EXPORT keyword.
 */

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

#if defined(_WIN32)
#define EXPORT EXTERN_C DLLEXPORT
#else
#if (defined(LINUX) || defined(MACOSX))
#define EXPORT EXTERN_C __attribute__ ((visibility ("default")))
#else
#define EXPORT EXTERN_C
#endif
#endif

#endif /* vertexcolors_h */
