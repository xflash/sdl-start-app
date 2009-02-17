#ifndef __INTERN_H__
#define __INTERN_H__

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <string>
#include <map>
#include <vector>
using namespace std;

#include "sys_types.h"
#include "exceptions.h"

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

struct Point {
  int16 x;
  int16 y;
};

struct Rect {
  int16 x;
  int16 y;
  int16 w;
  int16 h;
};

static Point getCenter(Rect* rect) {
  Point pt;
  pt.x=rect->x+rect->w/2;
  pt.y=rect->y+rect->h/2;
  return pt;
}

struct Frame{
  Rect loc;
};

struct FrameSet {
  string id;
  vector<Frame*> frames;
};

struct TileAnimation {
  string id;
  map<string, FrameSet*> framesets;
};
struct TileSheet {
  string id;
  int surfId;
  map<string, TileAnimation*> tileAnimations;
};


#endif // __INTERN_H__
