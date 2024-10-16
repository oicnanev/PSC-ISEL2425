#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <limits.h>

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#ifndef FALSE
#define FALSE   0
#endif/*FALSE*/
#ifndef TRUE
#define TRUE    (!FALSE)
#endif/*TRUE*/
typedef unsigned char bool;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;

#define PRINT_EXP(e) printf(#e " = %d\n", e)

#endif/*_COMMON_H*/