#include "Character.h"
#include "game.h"
#include "systemstub.h"
#include "resources.h"
#include "CharacterUpdater.h"
#include <iostream>
using namespace std;


Character::Character(SystemStub* stub, CharacterUpdater* updater): _stub(stub), _updater(updater){
  _dbg=false;
  _loc.x = Game::GAMESCREEN_W/2;
  _loc.y = Game::GAMESCREEN_H/2;
  _xd = _yd = 0;
}

void Character::init(Resources* res, string tilepath) {
  string tilesheet = tilepath.substr(0, tilepath.find('.'));
  string tilename = tilepath.substr(tilepath.find('.')+1);
  TileSheet* tileSheet = res->_tileSheets[tilesheet];
  _surfId = tileSheet->surfId;

  TileAnimation* peonTile=tileSheet->tileAnimations[tilename];
  _upSet = peonTile->framesets["up"];
  _downSet = peonTile->framesets["down"];
  _leftSet = peonTile->framesets["left"];
  _rightSet = peonTile->framesets["right"];

  _frameSet=_downSet;
  _frame=0;
  _animated=false;
}

void Character::update() {
  _updater->update(this);

  if(_animated) {
    _frame++;
    if(_frame>=_frameSet->frames.size())
      _frame=0;
  } else {
    _frameSet=_downSet;
    _frame=0;
  }

  _loc.x+=_xd;
  _loc.y+=_yd;

  _bbox.x = _loc.x;
  _bbox.y = _loc.y;
  _bbox.w = _frameSet->frames[_frame]->loc.w;
  _bbox.h = _frameSet->frames[_frame]->loc.h;
}


void Character::draw() {
  Frame* fr = _frameSet->frames[_frame];
  _blitter.x=fr->loc.x;
  _blitter.y=fr->loc.y;
  _blitter.w=fr->loc.w;
  _blitter.h=fr->loc.h;

  if(_dbg) {
    _stub->drawRect(&_bbox, 0xFF00007F);
    _updater->dbgDraw(this);
  }
  _stub->drawImage(_surfId, &_blitter, &_loc);
}


void Character::moveLeft() {
  _xd=-ACC_X; 
  _frameSet=_leftSet;  
  _animated=true;
}

void Character::moveRight() {
  _xd=ACC_X;  
  _frameSet=_rightSet; 
  _animated=true;
}

void Character::stopX() {
  _xd=0;
}

void Character::moveUp() {
  _yd=-ACC_Y;  
  _frameSet=_upSet;   
  _animated=true;
}

void Character::moveDown() {
  _yd=ACC_Y;
  _frameSet=_downSet;
  _animated=true;
}

void Character::stopY() {
  _yd=0;
}

void Character::checkStop() {
  if(_xd==0 && _yd==0)
    _animated=false;
}


