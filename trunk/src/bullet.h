#ifndef __BULLET_H__
#define __BULLET_H__

#include "intern.h"
#include "actor.h"
#include "actorpool.h"

class Resources;
class SystemStub;
class Game;
class Character;

class Bullet : public Actor {
public:
	void init(InitActorArgs* args);
	void draw();
	void move();
  void start(Character* character, float angle, float speed);

  void explose();

  Character* _origin;
  FrameSet* _frameSet;
  FrameSet* _standing;
  FrameSet* _explosingSet;
  SystemStub* _stub;
  Game* _game;
  int _surfId;
  Rect _blitter;
  Point _loc;
  Rect _bbox;
  uint _frame;
  float _speed;
  float _angle;
  float _sX;
  float _sY;

  bool _exploding;
};

class BulletPool : public ActorPool<Bullet> {
public:
  void init(int nb, Resources* res, SystemStub* stub, Game* game, string tilepath);
};


#endif
