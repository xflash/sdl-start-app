#ifndef __INTERN_H__
#define __INTERN_H__

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>

#include "sys_types.h"

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#endif // __INTERN_H__
