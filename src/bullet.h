#ifndef __BULLET_H__
#define __BULLET_H__

#include "intern.h"
#include "actor.h"
#include "actorpool.h"

class Resources;
class SystemStub;

class Bullet : public Actor {
public:
	void init(InitActorArgs* args);
	void draw();
	void move();
  void start(int16 x, int16 y, float angle, float speed);

  FrameSet* _frameSet;
  FrameSet* _explosingSet;
  SystemStub* _stub;
  int _surfId;
  Rect _blitter;
  Point _loc;
  float _speed;
  float _angle;
  float _sX;
  float _sY;
};

class BulletPool : public ActorPool<Bullet> {
public:
  void init(int nb, Resources* res, SystemStub* stub);
};


#endif
