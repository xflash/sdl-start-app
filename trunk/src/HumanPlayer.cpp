#include "HumanPlayer.h"
#include "Character.h"
#include "bullet.h"
#include "systemstub.h"
#include "resources.h"
#include <math.h>
#include <iostream>
using namespace std;

HumanPlayer::HumanPlayer(PlayerInput* pi, BulletPool* bullets): _pi(pi), _bullets(bullets){}

void HumanPlayer::update(Character* character) {

  if(_pi->dirMask & PlayerInput::DIR_LEFT)        character->moveLeft();
  else if(_pi->dirMask & PlayerInput::DIR_RIGHT)  character->moveRight();
  else                                            character->stopX();

  if(_pi->dirMask & PlayerInput::DIR_UP)          character->moveUp();
  else if(_pi->dirMask & PlayerInput::DIR_DOWN)   character->moveDown();
  else                                            character->stopY();

  character->checkStop();

  if(_pi->click) {
    //_pi->click = false;
    //float speed=0.3f*dist;
    angle = getAngle(&getCenter(character->getBBox()), &_pi->mouse);
      
    //float dist = sqrt(dX*dX + dY*dY);
    //angle+=da;
    da+=0.1f;

    float speed=10.0f;
    _bullets->getInstance()->start(character, angle-0.15f, speed);
    _bullets->getInstance()->start(character, angle-0.1f,  speed);
    _bullets->getInstance()->start(character, angle,      speed);
    _bullets->getInstance()->start(character, angle+0.1f,  speed);
    _bullets->getInstance()->start(character, angle+0.15f, speed);
  } else {
    //
    //da=0.0;
    da=0.0f;
  }
}

void HumanPlayer::dbgDraw(Character* character) {
  //
}
