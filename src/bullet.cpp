#include "bullet.h"
#include "resources.h"
#include "systemstub.h"
#include "game.h"
#include <math.h>

void BulletPool::init(int nb, Resources* res, SystemStub* stub) {
  TileSheet* bulletsSheet=res->_tileSheets["bullets"];
  int surfId = bulletsSheet->surfId;

  TileAnimation* bulletTile=bulletsSheet->tileAnimations["bullet"];

  InitActorArgs args(3);
  args[0]=(void*)surfId;
  args[1]=bulletTile;
  args[2]=stub;

  createActors(nb, &args);
}

void Bullet::init(InitActorArgs* args) {
  _surfId = (int)(*args)[0];
  TileAnimation* bulletTile= (TileAnimation*)(*args)[1];
  _frameSet= bulletTile->framesets["standing"];
  _explosingSet= bulletTile->framesets["explosing"];
  _stub= (SystemStub*)(*args)[2];
}

void Bullet::move() { 
  _loc.x+=_sX;
  _loc.y+=_sY;
  if( _loc.x>=Game::GAMESCREEN_W || _loc.x<=0 
    ||_loc.y>=Game::GAMESCREEN_H || _loc.y<=0 )
    exists(false);
}

void Bullet::draw() {
  _blitter.x=_frameSet->frames[0]->loc.x;
  _blitter.y=_frameSet->frames[0]->loc.y;
  _blitter.w=_frameSet->frames[0]->loc.w;
  _blitter.h=_frameSet->frames[0]->loc.h;

  _stub->drawImage(_surfId, &_blitter, &_loc);
}
	

void Bullet::start(int16 x, int16 y, float angle, float speed) {
  _speed=speed;
  _angle=angle;
  _loc.x=x;
  _loc.y=y;
  _sX = cos(_angle) * _speed;
  _sY = sin(_angle) * _speed;
}
