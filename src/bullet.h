#ifndef __BULLET_H__
#define __BULLET_H__

#include "intern.h"
#include "actor.h"
#include "actorpool.h"

class Resources;
class SystemStub;
class Game;
class Character;
class TiXmlElement;

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
  T_Characters* _characters;
  int _surfId;
  Point _loc;
  Rect _bbox;
  Rect _frameBlitter;
  Rect _dstBlitter;
  uint _frame;
  float _speed;
  float _angle;
  float _sX;
  float _sY;

  bool _exploding;
};

class BulletPool : public ActorPool<Bullet> {
public:
  BulletPool(Game* game, TiXmlElement* element);
};


#endif
