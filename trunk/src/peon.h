#ifndef __PEON_H__
#define __PEON_H__

#include "intern.h"

struct SystemStub;
struct Resources;

struct Peon {
  enum {
    ACC_X=  5,
    ACC_Y=  3,
  };
  SystemStub* _stub;
  Point _loc;
  Rect  _blitter;
  FrameSet* _currentFrameSet;
  int _frame;
  bool _moving;

  int16 _xd;
  int16 _yd;

  Peon(SystemStub* stub);
  
  void init(Resources* res);
  void update();
  void draw();

};

#endif // __PEON_H__
