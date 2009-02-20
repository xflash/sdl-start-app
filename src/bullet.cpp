#include "bullet.h"
#include "resources.h"
#include "systemstub.h"
#include "game.h"
#include "Character.h"
#include <math.h>

void BulletPool::init(int nb, Resources* res, SystemStub* stub, Game* game, string tilepath) {
  string tilesheet = tilepath.substr(0, tilepath.find('.'));
  string tilename = tilepath.substr(tilepath.find('.')+1);
  TileSheet* bulletsSheet=res->_tileSheets[tilesheet];
  int surfId = bulletsSheet->surfId;

  TileAnimation* bulletTile=bulletsSheet->tileAnimations[tilename];

  InitActorArgs args(4);
  args[0]=(void*)surfId;
  args[1]=bulletTile;
  args[2]=stub;
  args[3]=game;

  createActors(nb, &args);
}

void Bullet::init(InitActorArgs* args) {
  _surfId = (int)(*args)[0];
  TileAnimation* bulletTile= (TileAnimation*)(*args)[1];
  _standing= bulletTile->framesets["standing"];
  _explosingSet= bulletTile->framesets["explosing"];
  _stub= (SystemStub*)(*args)[2];
  _game= (Game*)(*args)[3];
}

void Bullet::start(Character* origin, float angle, float speed) {
  _origin=origin;
  _speed=speed;
  _angle=angle;
  _loc.x=origin->_bbox.x + origin->_bbox.w / 2;
  _loc.y=origin->_bbox.y + origin->_bbox.h / 2;
  _sX = cos(_angle) * _speed;
  _sY = sin(_angle) * _speed;
  _frameSet = _standing;
  _frame=0;
  _exploding = false;
}

void Bullet::move() { 
  _loc.x+=(int16)_sX;
  _loc.y+=(int16)_sY;
  
  _bbox.x = _loc.x;
  _bbox.y = _loc.y;
  _bbox.w = _frameSet->frames[_frame]->loc.w;
  _bbox.h = _frameSet->frames[_frame]->loc.h;

  if(_exploding) {
    explose();
    return;
  }

  if(_bbox.x>=(Game::GAMESCREEN_W-_bbox.w) || _bbox.x<=0 
    ||_bbox.y>=(Game::GAMESCREEN_H-_bbox.h) || _bbox.y<=0 ) {
      explose();
  }
  IT_Characters it;
  for(it=_game->_characters.begin(); it!=_game->_characters.end(); ++it) {
    Character* character=it->second;
    if(character != _origin && overlapRects(&character->_bbox, &_bbox)) {
      explose();
    }
  }
}

void Bullet::explose() {
  _exploding=true;
  _sX=0;
  _sY=0;
  _frameSet = _explosingSet;
  _frame++;
  if(_frame>=_frameSet->frames.size()) {
    exists(false);
  }
}

void Bullet::draw() {
  _blitter.x=_frameSet->frames[_frame]->loc.x;
  _blitter.y=_frameSet->frames[_frame]->loc.y;
  _blitter.w=_frameSet->frames[_frame]->loc.w;
  _blitter.h=_frameSet->frames[_frame]->loc.h;

  //_stub->drawRect(&_bbox, 0x0F0F0FFF);
  _stub->drawImage(_surfId, &_blitter, &_loc);
}
	

