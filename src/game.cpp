#include <ctime>
#include "systemstub.h"
#include "game.h"

Game::Game(SystemStub* stub, string datadir)
	: _stub(stub), _peon(stub), _res(stub, datadir) {
    
}

void Game::run() {
	_stub->init("Test", GAMESCREEN_W, GAMESCREEN_H);
  _res.loadAll();
  _peon.init(&_res);
	mainLoop();
	_stub->destroy();
}


void Game::mainLoop() {
  Point locMsg;
  locMsg.x=0; locMsg.y=0;
  static char buf[256];

  while (!_stub->_pi.quit) {
  	_stub->processEvents();
    _peon.update();
    _peon.draw();
    if(_stub->_pi.escape)
      break;

		uint32 delay = updateTiming();
    sprintf(buf, "FrameTime: %d ms",delay);
    _stub->drawString(&locMsg, buf);
    _stub->updateScreen();
	}
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
