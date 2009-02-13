#ifndef __ANIMATED_H__
#define __ANIMATED_H__

#include "intern.h"

struct Animated {
  
  Animated();

  FrameSet* _currentFrameSet;
  FrameSet* _defaultFrameSet;
  uint16 _frame;
  bool _animated;

  void update();
};

#endif // __ANIMATED_H__
