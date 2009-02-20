#ifndef __Maps_H__
#define __Maps_H__

#include "intern.h"
#include <string>
#include <map>
#include <vector>
using namespace std;

class TiXmlElement;
class Game;
class SystemStub;

class Map {
private:
  uint16 _w;
  uint16 _h;
  TileSheet* _tileSheet;
  SystemStub* _stub;
  vector<string> _rows;
public:
  Map(Game* game, TiXmlElement* element);
  void draw(Rect* blit);
};

class Maps {
private:
  Game* _game;
  map<string, Map*> _maps;
public:
  Maps(Game* game);
  void loadAll(string datadir, string filename);
  Map* getMap(string mapId);
};

#endif // __Maps_H__
