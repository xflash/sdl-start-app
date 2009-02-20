#ifndef __HumanSeeker_H__
#define __HumanSeeker_H__

#include "intern.h"
#include "CharacterUpdater.h"

class SystemStub;
class Character;
class TiXmlElement;
class Game;

class HumanSeeker : public CharacterUpdater {
private:
  int16 _sightRadius;
  int16 _fightRadius;
  SystemStub* _stub;
  Character* _target;
  int _dist;
public:
  HumanSeeker(Game* game, TiXmlElement* element);
  
  void update(Character* character);
  void dbgDraw(Character* character);
};

#endif // __HumanSeeker_H__
