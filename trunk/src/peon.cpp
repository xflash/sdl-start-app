#include "peon.h"
#include "game.h"
#include "systemstub.h"
#include "resources.h"
#include <iostream>
using namespace std;


Peon::Peon(SystemStub* stub): Blittable(stub),  _stub(stub){
  _loc.x = Game::GAMESCREEN_W/2;
  _loc.y = Game::GAMESCREEN_H/2;
  _xd = _yd = 0;
}

void Peon::init(Resources* res) {
  TileSheet* tileSheet = res->_tileSheets["tilesW3"];
  _surfId = tileSheet->surfId;

  TileAnimation* peonTile=tileSheet->tileAnimations["orc"];
  _upSet = peonTile->framesets["up"];
  _downSet = peonTile->framesets["down"];
  _leftSet = peonTile->framesets["left"];
  _rightSet = peonTile->framesets["right"];

  _defaultFrameSet=_downSet;
  _currentFrameSet=_defaultFrameSet;
}


void Peon::update() {
  if(_stub->_pi.dirMask & PlayerInput::DIR_LEFT)        { _xd=-ACC_X; _currentFrameSet=_leftSet;  _animated=true;}
  else if(_stub->_pi.dirMask & PlayerInput::DIR_RIGHT)  { _xd=ACC_X;  _currentFrameSet=_rightSet; _animated=true;}
  else                                                  { _xd=0;      }

  if(_stub->_pi.dirMask & PlayerInput::DIR_UP)          { _yd=-ACC_Y;  _currentFrameSet=_upSet;   _animated=true;}
  else if(_stub->_pi.dirMask & PlayerInput::DIR_DOWN)   { _yd=ACC_Y;   _currentFrameSet=_downSet; _animated=true;}
  else                                                  { _yd=0;       }

  if(_xd==0 && _yd==0)  _animated=false;

  Animated::update();

  _loc.x+=_xd;
  _loc.y+=_yd;
}

void Peon::draw() {
  Blittable::draw(_currentFrameSet->frames[_frame], &_loc);
}
