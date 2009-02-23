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

struct MapTile {
  uint16 resid;
  bool collision;
};

class Map {
private:
  TileSheet* _tileSheet;
  //uint _ntiles;
  uint _width;
  uint _heigth;
  MapTile* _tiles;
public:
  Map(Game* game, string datadir, TiXmlElement* element);
  void draw(SystemStub* stub, Rect* blit);
};

class Maps {
private:
  map<string, Map*> _maps;
public:
  Maps(Game* game, string datadir, string filename);
  Map* getMap(string mapId);
};

#endif // __Maps_H__
