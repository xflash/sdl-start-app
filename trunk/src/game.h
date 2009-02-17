#ifndef __GAME_H__
#define __GAME_H__

#include "intern.h"
#include "Character.h"
#include "resources.h"
#include "bullet.h"
#include <string>
#include <vector>
using namespace std;

class SystemStub;

class Game {
public:
  enum {
    GAMESCREEN_W = 640,
    GAMESCREEN_H = 480,
  };

  SystemStub *_stub;
  vector<Character*> _characters;
  Character _peon;
  Resources _res;
  BulletPool _bullets;

	Game(SystemStub * stub, string datadir);

	void run();
  void move();
  void draw();
	void mainLoop();
  uint32 updateTiming();

};

#endif // __GAME_H__
