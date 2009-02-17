#include "Character.h"
#include "game.h"
#include "systemstub.h"
#include "resources.h"
#include <iostream>
using namespace std;


Character::Character(SystemStub* stub, string tilename): 
  _tilename(tilename), _stub(stub){
  _loc.x = Game::GAMESCREEN_W/2;
  _loc.y = Game::GAMESCREEN_H/2;
  _xd = _yd = 0;
}

void Character::init(Resources* res) {
  TileSheet* tileSheet = res->_tileSheets["tilesW3"];
  _surfId = tileSheet->surfId;

  TileAnimation* peonTile=tileSheet->tileAnimations[_tilename];
  _upSet = peonTile->framesets["up"];
  _downSet = peonTile->framesets["down"];
  _leftSet = peonTile->framesets["left"];
  _rightSet = peonTile->framesets["right"];

  _defaultFrameSet=_downSet;
  _currentFrameSet=_defaultFrameSet;
}

void Character::updateInput() {
  if(_stub->_pi.dirMask & PlayerInput::DIR_LEFT)        { _xd=-ACC_X; _currentFrameSet=_leftSet;  _animated=true;}
  else if(_stub->_pi.dirMask & PlayerInput::DIR_RIGHT)  { _xd=ACC_X;  _currentFrameSet=_rightSet; _animated=true;}
  else                                                  { _xd=0;      }

  if(_stub->_pi.dirMask & PlayerInput::DIR_UP)          { _yd=-ACC_Y;  _currentFrameSet=_upSet;   _animated=true;}
  else if(_stub->_pi.dirMask & PlayerInput::DIR_DOWN)   { _yd=ACC_Y;   _currentFrameSet=_downSet; _animated=true;}
  else                                                  { _yd=0;       }

  if(_xd==0 && _yd==0)  _animated=false;
}

void Character::update() {

  Animated::update();

  _loc.x+=_xd;
  _loc.y+=_yd;
}


void Character::draw() {
  Frame* fr = _currentFrameSet->frames[_frame];
  _blitter.x=fr->loc.x;
  _blitter.y=fr->loc.y;
  _blitter.w=fr->loc.w;
  _blitter.h=fr->loc.h;

  _stub->drawImage(_surfId, &_blitter, &_loc);
}
