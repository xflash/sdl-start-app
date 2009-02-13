#ifndef __PEON_H__
#define __PEON_H__

#include "intern.h"
#include "animated.h"
#include "blittable.h"

struct SystemStub;
struct Resources;

struct Peon: Animated, Blittable {
  enum {
    ACC_X=  5,
    ACC_Y=  3,
  };

  FrameSet* _upSet;
  FrameSet* _downSet;
  FrameSet* _leftSet;
  FrameSet* _rightSet;

  SystemStub* _stub;
  Point _loc;
  int16 _xd;
  int16 _yd;

  Peon(SystemStub* stub);
  
  void init(Resources* res);
  void update();
  void draw();

};

#endif // __PEON_H__
