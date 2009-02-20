#ifndef __GAME_H__
#define __GAME_H__

#include "intern.h"
#include "resources.h"
#include "Maps.h"
#include <string>
using namespace std;

class SystemStub;
class CharacterUpdater;
class Character;
class BulletPool;

class Game {
private:
  string _datadir;
  Resources _res;
  Maps _maps;
  SystemStub *_stub;
  BulletPool* _bullets;
  T_Characters _characters;

public:
  enum {
    GAMESCREEN_W = 640,
    GAMESCREEN_H = 480,
  };

public:
  Game(SystemStub * stub, string datadir);
	void run();

  Resources* getRessources() { return &_res; }
  SystemStub* getStub() { return _stub; }
  T_Characters* getCharacters() { return &_characters; }

private:
  void move();
  void draw();
  void mainLoop();
  uint32 updateTiming();
  void init();
  void close();
};

#endif // __GAME_H__
