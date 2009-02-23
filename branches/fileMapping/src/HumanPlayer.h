#ifndef __HumanPlayer_H__
#define __HumanPlayer_H__

#include "intern.h"
#include "CharacterUpdater.h"

class Character;
struct PlayerInput;
class BulletPool;

class HumanPlayer: public CharacterUpdater {
private:
  PlayerInput* _pi;
  BulletPool* _bullets;
  float angle;
  float da;
public:
  HumanPlayer(PlayerInput* pi, BulletPool* bullets);

  void update(Character* character);
  void dbgDraw(Character* character);
};

#endif // __HumanPlayer_H__
