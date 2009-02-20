#include "HumanSeeker.h"
#include "Character.h"
#include "systemstub.h"
#include "Game.h"
#include "tinyXML/TinyXML.h"

HumanSeeker::HumanSeeker(Game* game, TiXmlElement* element): 
  _stub(game->getStub()) {
  
  _sightRadius=atoi(element->Attribute("sightradius"));
  _fightRadius=atoi(element->Attribute("fightradius"));;
  _target= game->getCharacters()->find(element->Attribute("target"))->second;

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

  _dist = getDistance(&getCenter(character->getBBox()), &getCenter(_target->getBBox()));
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
    _stub->drawCircle(&getCenter(character->getBBox()), _sightRadius, 0x0000ff1f, true);
  else {
    _stub->drawCircle(&getCenter(character->getBBox()), _sightRadius, 0x0000ffff);
    if(_dist<=_fightRadius)
      _stub->drawCircle(&getCenter(character->getBBox()), _fightRadius, 0x0ff0001f, true);
    else
      _stub->drawCircle(&getCenter(character->getBBox()), _fightRadius, 0x0ff000ff);
  }

  //_stub->drawString(&character->_loc, "Distance %d", _dist);
}

