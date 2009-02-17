#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "intern.h"
#include "animated.h"

class SystemStub;
class Resources;

class Character: public Animated {
public:
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
  Rect  _blitter;
  uint8 _surfId;
  string _tilename;

  Character(SystemStub* stub, string tilename);
  
  void init(Resources* res);
  void update();
  void updateInput();
  void draw();

};

#endif // __CHARACTER_H__
