#ifndef __GAME_H__
#define __GAME_H__

#include "intern.h"
#include "resources.h"
#include <string>
#include <map>
#include <vector>
using namespace std;

class SystemStub;
class CharacterUpdater;
class Character;
class BulletPool;
class TiXmlElement;

typedef map<string, Character*> T_Characters;
typedef T_Characters::iterator IT_Characters;

class Game {
public:
  enum {
    GAMESCREEN_W = 640,
    GAMESCREEN_H = 480,
  };

  string _datadir;
  Resources _res;
  SystemStub *_stub;
  BulletPool* _bullets;
  T_Characters _characters;

	Game(SystemStub * stub, string datadir);

	void run();
  void move();
  void draw();
	void mainLoop();
  uint32 updateTiming();

private:
  void init();
  Character* createCharacterFromXmlElement(TiXmlElement* element, CharacterUpdater* updater);
  void close();

};

#endif // __GAME_H__
