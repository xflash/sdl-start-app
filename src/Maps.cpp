#include "Maps.h"
#include "Game.h"
#include "tinyXML/TinyXML.h"
#include "systemstub.h"
#include <iostream>
#include <sstream>

Maps::Maps(Game* game, string datadir, string filename) {
  ostringstream ostr;
  ostr << datadir << "/" << filename;
  cout << "Loading Maps from ("<<ostr.str()<<")" << endl;

  TiXmlDocument doc(ostr.str().c_str());
  if (!doc.LoadFile())
    throw new SystemException("Could not load test file '%s'. Error='%s'.", filename.c_str(), doc.ErrorDesc() );

  TiXmlNode* maps = doc.FirstChild("maps");
  assert(maps);
  for(TiXmlElement* mapElement=maps->FirstChildElement();mapElement;mapElement=mapElement->NextSiblingElement()) {
    _maps[mapElement->Attribute("id")] = new Map(game, datadir, mapElement);
  }
}

Map* Maps::getMap(string mapId) {
  return _maps[mapId];
}

Map::Map(Game* game, string datadir, TiXmlElement* mapElement) {
  cout << "\tRead Map id:"<<mapElement->Attribute("id") << endl;
  _tileSheet = game->getRessources()->getTileSheet(mapElement->Attribute("tilepath"));

  string filename = mapElement->Attribute("filename");
  ostringstream ostr;
  ostr << datadir << "/" << filename;
  FILE* f = fopen(ostr.str().c_str(), "rb");
  if(!f)
    throw new SystemException("Could not load map file '%s'.", filename.c_str());

  fread(&_width, sizeof(uint), 1, f);
  fread(&_heigth, sizeof(uint), 1, f);

  uint nb = _width*_heigth;
  _tiles = (MapTile*)calloc(nb, sizeof(MapTile));
  int rd = fread(_tiles, sizeof(MapTile), nb, f);
  if(rd!=nb) 
    throw new SystemException("Could not load map file '%s'.", filename.c_str());
  //rd = fread(_tiles, sizeof(MapTile), 1, f);
  //int rd = fread(_tiles, sizeof(MapTile), _width*_heigth, f);
  
  fclose(f);
}

/** Drawings **/

void Map::draw(SystemStub* stub, Rect *blit) {
/*
for (uint l=0; l<_layers.size(); l++) {
    _layers[l]->draw(stub, blit, _tileSheet->surfId, &_tiles);
  }
  */
}

/*
void MapLayer::draw(SystemStub* stub, Rect *blit, int surfId, vector<MapTile*>* tiles) {
  Rect dst;
  dst.x=dst.y=0;

	for (uint r=0; r<_rows.size(); r++) {
    string rowContent=_rows[r];
    dst.x=0;
    for (uint c=0; c<rowContent.size(); c+=2) {
      int tile = atoi(rowContent.substr(c, 2).c_str());
      if(tile<=0) continue;
      //Frame* f = _tileSheet->tiles[tile];
      Frame* f = tiles->at(tile)->getFrame();
      dst.w=f->loc.w;
      dst.h=f->loc.h;
      dst.y=r*f->loc.h;
      dst.x=(c/2)*f->loc.w;
      stub->drawImage(surfId, &f->loc, &dst);
    }
  }
}
*/

