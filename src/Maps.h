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

class MapTile {
private:
  Frame* _resFrame;
  bool _collision;
public:
  MapTile(Game* game, TileSheet* tileSheet, TiXmlElement* element);
  void draw(SystemStub* stub, Rect* blit);
  Frame* getFrame() { return _resFrame; }
};

class MapLayer {
private:
  uint16 _w;
  uint16 _h;
  vector<string> _rows;
public:
  MapLayer(TiXmlElement* element);
  void draw(SystemStub* stub, Rect* blit, int surfId, vector<MapTile*>* tiles);
};

class Map {
private:
  vector<MapLayer*> _layers;
  vector<MapTile*> _tiles;
  TileSheet* _tileSheet;
public:
  Map(Game* game, TiXmlElement* element);
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
