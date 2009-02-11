#ifndef __PEON_H__
#define __PEON_H__

#include "intern.h"

struct SystemStub;

struct Peon {
  SystemStub* _stub;
  int16 _x;
  int16 _y;
  int16 _xd;
  int16 _yd;

  Peon(SystemStub* stub);
  
  void update();
  void draw();


};

#endif // __PEON_H__
