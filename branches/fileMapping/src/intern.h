#ifndef __INTERN_H__
#define __INTERN_H__

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <string>
#include <map>
#include <vector>
#include <math.h>
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

static void copyRects(Rect* src, Rect* target) {
  target->x = src->x;
  target->y = src->y;
  target->w = src->w;
  target->h = src->h;
}

static bool overlapRects(Rect* a, Rect* b) {
  return ((a->x<(b->x+b->w)) &&((a->x+a->w)>b->x)
        &&(a->y<(b->y+b->h)) &&((a->y+a->h)>b->y));
}

static Point getCenter(Rect* rect) {
  Point pt;
  pt.x=rect->x+rect->w/2;
  pt.y=rect->y+rect->h/2;
  return pt;
}

static uint getDistance(Point* p1, Point* p2) {
  uint32 dx = abs(p2->x-p1->x);
  uint32 dy = abs(p2->y-p1->y);
  return (uint)sqrt((double)dx*dx + dy*dy);
}

static float getAngle(Point* p1, Point* p2) {
  int dY = p2->y - p1->y;
  int dX = p2->x - p1->x;
  return atan2((float)dY, (float)dX);
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
  vector<Frame*> tiles;
};


class Character;

typedef map<string, Character*> T_Characters;
typedef T_Characters::iterator IT_Characters;



#endif // __INTERN_H__
