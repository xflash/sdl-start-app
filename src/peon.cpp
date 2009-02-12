#include "peon.h"
#include "game.h"
#include "systemstub.h"
#include "resources.h"
#include <iostream>
using namespace std;

static TileSheet* tileSheet;
static TileAnimation* peonTile;
static FrameSet* upSet;
static FrameSet* downSet;
static FrameSet* leftSet;
static FrameSet* rightSet;

Peon::Peon(SystemStub* stub)
  :_stub(stub){
  _loc.x = Game::GAMESCREEN_W/2;
  _loc.y = Game::GAMESCREEN_H/2;
  _xd = _yd = 0;
  _frame=0;
  _currentFrameSet=NULL;
  _moving=false;
}

void Peon::init(Resources* res) {
  tileSheet = res->_tileSheets["tilesW3"];
  peonTile = tileSheet->tileAnimations["orc"];
  upSet = peonTile->framesets["up"];
  downSet = peonTile->framesets["down"];
  leftSet = peonTile->framesets["left"];
  rightSet = peonTile->framesets["right"];

  _currentFrameSet=downSet;
}


void Peon::update() {
  if(_stub->_pi.dirMask & PlayerInput::DIR_LEFT)        { _xd=-ACC_X; _currentFrameSet=leftSet;  _moving=true;}
  else if(_stub->_pi.dirMask & PlayerInput::DIR_RIGHT)  { _xd=ACC_X;  _currentFrameSet=rightSet; _moving=true;}
  else                                                  { _xd=0;      }

  if(_stub->_pi.dirMask & PlayerInput::DIR_UP)          { _yd=-ACC_Y;  _currentFrameSet=upSet;   _moving=true;}
  else if(_stub->_pi.dirMask & PlayerInput::DIR_DOWN)   { _yd=ACC_Y;   _currentFrameSet=downSet; _moving=true;}
  else                                                  { _yd=0;       }

  if(_xd==0 && _yd==0)  _moving=false;

  if(_moving) {
    _frame++;
    if(_frame>=_currentFrameSet->frames.size())
      _frame=0;
  } else {
    _currentFrameSet=downSet;
    _frame=1;
  }

  _loc.x+=_xd;
  _loc.y+=_yd;
}

void Peon::draw() {
  _blitter.x=_currentFrameSet->frames[_frame]->loc.x;
  _blitter.y=_currentFrameSet->frames[_frame]->loc.y;
  _blitter.w=_currentFrameSet->frames[_frame]->loc.w;
  _blitter.h=_currentFrameSet->frames[_frame]->loc.h;

  _stub->drawImage(tileSheet->surfId, &_blitter, &_loc);
}
