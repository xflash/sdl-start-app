#include <ctime>
#include "systemstub.h"
#include "game.h"
#include <math.h>

Game::Game(SystemStub* stub, string datadir)
	: _stub(stub), _peon(stub, "peon"), _res(stub, datadir) {
}

void Game::run() {
	_stub->init("Test", GAMESCREEN_W, GAMESCREEN_H);
  _res.loadAll();
  _peon.init(&_res);
  _peon._loc.x=100;
  _bullets.init(500, &_res, _stub);

  _characters.push_back(new Character(_stub, "orc"));
	
		for (uint i = 0; i < _characters.size(); i++) {
			Character* act=_characters[i];
  		act->init(&_res);
		}

  mainLoop();
	_stub->destroy();
}


void Game::mainLoop() {
  while (!_stub->_pi.quit) {
  	_stub->processEvents();
    if(_stub->_pi.escape) break;
    move();
    draw();
    _stub->updateScreen();
	}
}

class PlayerUpdater {
private:
  PlayerInput* _pi;
  BulletPool* _bullets;
  uint32 _frames;
public:
  PlayerUpdater(PlayerInput* pi, BulletPool* bullets):_pi(pi), _bullets(bullets),_frames(0) {}

  void updateCharacter(Character* character) {

    character->updateInput();
    character->update();

    if(_pi->click) {
      //_pi->click = false;
      //float speed=0.3f*dist;
      _frames++;
      if(_frames%2) {
        shoot(character);
      }
    }
  }

    void shoot(Character* character) {
      float dY = (float) _pi->mouseY-character->_loc.y;
      float dX = (float) _pi->mouseX-character->_loc.x;
      float angle = atan2(dY, dX);
      float dist = sqrt(dX*dX + dY*dY);

      float speed=10.3f;
      int16 sx = character->_loc.x;
      int16 sy = character->_loc.y;
      _bullets->getInstance()->start(sx, sy, angle-0.15, speed);
      _bullets->getInstance()->start(sx, sy, angle-0.1,  speed);
      _bullets->getInstance()->start(sx, sy, angle,      speed);
      _bullets->getInstance()->start(sx, sy, angle+0.1,  speed);
      _bullets->getInstance()->start(sx, sy, angle+0.15, speed);
    }
};

void Game::move() {
  static PlayerUpdater pu(&_stub->_pi, &_bullets);
  pu.updateCharacter(&_peon);

  for (uint i = 0; i < _characters.size(); i++) {
	  Character* act=_characters[i];
	  act->update();
  }

  _bullets.move();
}

void Game::draw() {
  static Point locMsg;
  static char buf[256];
  static Point locMouse;
  locMouse.x = _stub->_pi.mouseX;
  locMouse.y = _stub->_pi.mouseY;

  _peon.draw();
  _stub->drawLine(&_peon._loc, &locMouse);

	for (uint i = 0; i < _characters.size(); i++) {
		Character* act=_characters[i];
		act->draw();
	}

  _bullets.draw();

  locMsg.y=locMsg.x=0;
  static int msgRowSize=10;

  uint32 delay = updateTiming();
  sprintf(buf, "FrameTime: %d ms",delay);
  _stub->drawString(&locMsg, buf);
  locMsg.y+=msgRowSize;

  sprintf(buf, "Bullets: %d/%d",_bullets.getNum(), _bullets.getNumMax());
  _stub->drawString(&locMsg, buf);
  locMsg.y+=msgRowSize;

  sprintf(buf, "Mouse: (%d,%d) %s", _stub->_pi.mouseX, _stub->_pi.mouseY, (_stub->_pi.click)?"Click":"");
  _stub->drawString(&locMsg, buf);
  locMsg.y+=msgRowSize;

}


uint32 Game::updateTiming() {
	static uint32 tstamp = 0;
	int32 delay = _stub->getTimeStamp() - tstamp;
	int32 pause = (_stub->_pi.dbgMask & PlayerInput::DF_FASTMODE) ? 20 : 30;
	pause -= delay;
	if (pause > 0) {
		_stub->sleep(pause);
	}
	tstamp = _stub->getTimeStamp();
  return delay;
}
