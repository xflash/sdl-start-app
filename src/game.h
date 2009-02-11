#ifndef __GAME_H__
#define __GAME_H__

#include "intern.h"
#include "peon.h"

struct SystemStub;


struct Game {
  enum {
    GAMESCREEN_W = 640,
    GAMESCREEN_H = 480,
  };

  SystemStub *_stub;
  Peon _peon;

	Game(SystemStub *);

	void run();
	void mainLoop();
  void updateTiming();

};

#endif // __GAME_H__
