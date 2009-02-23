#include "Character.h"
#include "Game.h"
#include "systemstub.h"
#include "resources.h"
#include "CharacterUpdater.h"
#include <iostream>
using namespace std;
#include "tinyXML/TinyXML.h"


Character::Character(Game* game, CharacterUpdater* updater, TiXmlElement* elementCharacter):
  _stub(game->getStub()), _updater(updater){
  _dbg=false;
  _xd = _yd = 0;

  const char* dbg = elementCharacter->Attribute("dbg");
  if(dbg!=NULL)
    _dbg=_stricmp("true", dbg)==0;
  _loc.x=atoi(elementCharacter->Attribute("x"));
  _loc.y=atoi(elementCharacter->Attribute("y"));

  TiXmlElement* bbox = elementCharacter->FirstChildElement("bbox");
  _bbox.x=_loc.x + atoi(bbox->Attribute("x"));
  _bbox.y=_loc.y + atoi(bbox->Attribute("y"));
  _bbox.w=atoi(bbox->Attribute("w"));
  _bbox.h=atoi(bbox->Attribute("h"));

  string tilepath = elementCharacter->Attribute("tilepath");
  string tilesheet = tilepath.substr(0, tilepath.find('.'));
  string tilename = tilepath.substr(tilepath.find('.')+1);
  TileSheet* tileSheet = game->getRessources()->getTileSheet(tilesheet);
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
  if(_updater!=NULL)
    _updater->update(this);

  if(_bbox.x>=(Game::GAMESCREEN_W-_bbox.w) || _bbox.x<=0 
    ||_bbox.y>=(Game::GAMESCREEN_H-_bbox.h) || _bbox.y<=0 ) {
      stopX();
      stopY();
      checkStop();
  }

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

  _bbox.x+=_xd;
  _bbox.y+=_yd;
//  _bbox.x = _loc.x;
//  _bbox.y = _loc.y;
  //_bbox.w = _frameSet->frames[_frame]->loc.w;
  //_bbox.h = _frameSet->frames[_frame]->loc.h;
}


void Character::draw() {
  Frame* fr = _frameSet->frames[_frame];
  _frameBlitter.x=fr->loc.x;
  _frameBlitter.y=fr->loc.y;
  _frameBlitter.w=fr->loc.w;
  _frameBlitter.h=fr->loc.h;

  _dstBlitter.x=_loc.x;
  _dstBlitter.y=_loc.y;
  _dstBlitter.w=_frameBlitter.w;
  _dstBlitter.h=_frameBlitter.h;

  _stub->drawImage(_surfId, &_frameBlitter, &_dstBlitter);

  if(_dbg) {
    _stub->drawRect(&_bbox, 0xFF00007F);
    if(_updater!=NULL)
      _updater->dbgDraw(this);
  }
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


