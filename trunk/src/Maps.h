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

class MapLayer {
private:
  uint16 _w;
  uint16 _h;
  vector<string> _rows;
  TileSheet* _tileSheet;
  SystemStub* _stub;
public:
  MapLayer(Game* game, TiXmlElement* element);
  void draw(Rect* blit);
};

class Map {
private:
  SystemStub* _stub;
  vector<MapLayer*> _layers;
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
