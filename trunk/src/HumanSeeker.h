#ifndef __HumanSeeker_H__
#define __HumanSeeker_H__

#include "intern.h"
#include "CharacterUpdater.h"

class SystemStub;
class Character;

class HumanSeeker : public CharacterUpdater {
private:
  int16 _radius;
  SystemStub* _stub;
public:
  HumanSeeker(SystemStub* systemstub, int16 radius);
  
  void update(Character* character);
  void dbgDraw(Character* character);
};

#endif // __HumanSeeker_H__
