#include "HumanSeeker.h"
#include "Character.h"
#include "systemstub.h"

HumanSeeker::HumanSeeker(SystemStub* systemstub, int16 sightRadius, int16 fightRadius, Character* target): 
_stub(systemstub), _sightRadius(sightRadius), _fightRadius(fightRadius), _target(target) {
}

void HumanSeeker::update(Character* character) {
  //throw new SystemException("TODO HumanSeeker::update()");
/*
int r=((double)rand()/(RAND_MAX+1))*4;
  switch(r) {
    case 0: character->moveLeft(); break;
    case 1: character->moveRight(); break;
    //case 2: character->moveLeft(); break;
    //case 3: character->moveLeft(); break;
    default: break;
  }
  */

  _dist = getDistance(&character->_loc, &_target->_loc);
  if(_dist<=_sightRadius) {
    //
  }
  if(_dist<=_fightRadius) {
    //
  }
}

void HumanSeeker::dbgDraw(Character* character) {
  //throw new SystemException("TODO HumanSeeker::dbgDraw()");
  if(_dist<=_sightRadius)
    _stub->drawCircle(&getCenter(&character->_bbox), _sightRadius, 0x0000ff1f, true);
  else {
    _stub->drawCircle(&getCenter(&character->_bbox), _sightRadius, 0x0000ffff);
    if(_dist<=_fightRadius)
      _stub->drawCircle(&getCenter(&character->_bbox), _fightRadius, 0x0ff0001f, true);
    else
      _stub->drawCircle(&getCenter(&character->_bbox), _fightRadius, 0x0ff000ff);
  }

  //_stub->drawString(&character->_loc, "Distance %d", _dist);
}

