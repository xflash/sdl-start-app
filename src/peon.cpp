#include "peon.h"
#include "game.h"
#include "systemstub.h"
#include "resources.h"
#include <iostream>
using namespace std;

#define ACC_X 5

Peon::Peon(SystemStub* stub)
  :_stub(stub) {
  _x = Game::GAMESCREEN_W/2;
  _y = Game::GAMESCREEN_H/2;
  _xd = _yd = 0;
}

void Peon::update() {
  //_xd = _yd = 0;
  if(_stub->_pi.dirMask & PlayerInput::DIR_LEFT) {
    cout << "Moving Peon on Left"<<endl;
    _stub->_pi.dirMask &= ~PlayerInput::DIR_LEFT;
    _xd=-ACC_X;
  }else if(_stub->_pi.dirMask & PlayerInput::DIR_RIGHT) {
    cout << "Moving Peon on Right"<<endl;
    _stub->_pi.dirMask &= ~PlayerInput::DIR_RIGHT;
    _xd=ACC_X;
  } else {
    _xd=0;
  }
  _x+=_xd;
  _y+=_yd;
}

void Peon::draw() {
  _stub->draw(Resources::PEON_SPRITE_ID, _x, _y);
}
