#include "HumanSeeker.h"
#include "Character.h"
#include "systemstub.h"

HumanSeeker::HumanSeeker(SystemStub* systemstub, int16 radius): _stub(systemstub), _radius(radius) {
}

void HumanSeeker::update(Character* character) {
  //throw new SystemException("TODO HumanSeeker::update()");
}

void HumanSeeker::dbgDraw(Character* character) {
  //throw new SystemException("TODO HumanSeeker::dbgDraw()");
  _stub->drawCircle(&getCenter(&character->_bbox), _radius, 0x0f0f0fff);
}

