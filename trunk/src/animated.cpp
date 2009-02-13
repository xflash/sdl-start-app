#include "animated.h"

Animated::Animated() { 
  _frame=0;
  _currentFrameSet=NULL;
  _animated=false;
}

void Animated::update() {

  if(_animated) {
    _frame++;
    if(_frame>=_currentFrameSet->frames.size())
      _frame=0;
  } else {
    _currentFrameSet=_defaultFrameSet;
    _frame=1;
  }
}

