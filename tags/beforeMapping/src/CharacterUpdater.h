#ifndef __CharacterUpdater_H__
#define __CharacterUpdater_H__

#include "intern.h"

class Character;

class CharacterUpdater {
public:
  virtual void update(Character* character)=0;
  virtual void dbgDraw(Character* character)=0;
};

#endif // __CharacterUpdater_H__
