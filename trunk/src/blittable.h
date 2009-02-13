#ifndef __BLITTABLE_H__
#define __BLITTABLE_H__

#include "intern.h"

struct SystemStub;

struct Blittable {

  SystemStub* _stub;
  
  Blittable(SystemStub* stub);

  Rect  _blitter;
  uint8 _surfId;

  
  void draw(Frame* fr, Point* loc);
};

#endif // __BLITTABLE_H__
