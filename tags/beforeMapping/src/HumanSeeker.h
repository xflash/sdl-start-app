#ifndef __HumanSeeker_H__
#define __HumanSeeker_H__

#include "intern.h"
#include "CharacterUpdater.h"

class SystemStub;
class Character;

class HumanSeeker : public CharacterUpdater {
private:
  int16 _sightRadius;
  int16 _fightRadius;
  SystemStub* _stub;
  Character* _target;
  int _dist;
public:
  HumanSeeker(SystemStub* systemstub, int16 sightRadius, int16 fightRadius, Character* target);
  
  void update(Character* character);
  void dbgDraw(Character* character);
};

#endif // __HumanSeeker_H__
