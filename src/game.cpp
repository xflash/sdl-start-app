/* REminiscence - Flashback interpreter
 * Copyright (C) 2005-2007 Gregory Montoir
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <ctime>
#include "systemstub.h"
#include "game.h"


Game::Game(SystemStub* stub)
	: _stub(stub), _peon(_stub) {
}

void Game::run() {
	_stub->init("Test", GAMESCREEN_W, GAMESCREEN_H);
	mainLoop();
	_stub->destroy();
}


void Game::mainLoop() {
	while (!_stub->_pi.quit) {
  	_stub->processEvents();

    _peon.update();

    _peon.draw();
    
		updateTiming();
    _stub->updateScreen();
	}
}

void Game::updateTiming() {
	static uint32 tstamp = 0;
	int32 delay = _stub->getTimeStamp() - tstamp;
	int32 pause = (_stub->_pi.dbgMask & PlayerInput::DF_FASTMODE) ? 20 : 30;
	pause -= delay;
	if (pause > 0) {
		_stub->sleep(pause);
	}
	tstamp = _stub->getTimeStamp();
}
