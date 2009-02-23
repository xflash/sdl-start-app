#include "Maps.h"
#include "Game.h"
#include "tinyXML/TinyXML.h"
#include "systemstub.h"
#include <iostream>
#include <sstream>

Maps::Maps(Game* game):_game(game) { }

void Maps::loadAll(string datadir, string filename) {
  ostringstream ostr;
  ostr << datadir << "/" << filename;
  cout << "Loading Maps from ("<<ostr.str()<<")" << endl;

  TiXmlDocument doc(ostr.str().c_str());
  if (!doc.LoadFile())
    throw new SystemException("Could not load test file '%s'. Error='%s'.", filename.c_str(), doc.ErrorDesc() );

  TiXmlNode* maps = doc.FirstChild("maps");
  assert(maps);
  for(TiXmlElement* mapElement=maps->FirstChildElement();mapElement;mapElement=mapElement->NextSiblingElement()) {
    _maps[mapElement->Attribute("id")] = new Map(_game, mapElement);
  }
}

Map* Maps::getMap(string mapId) {
  return _maps[mapId];
}

Map::Map(Game* game, TiXmlElement* mapElement):_stub(game->getStub()) {
  cout << "\tRead Map id:"<<mapElement->Attribute("id") << endl;
  for(TiXmlElement* layerElement=mapElement->FirstChildElement("layer");layerElement;layerElement=layerElement->NextSiblingElement()) {
    _layers.push_back(new MapLayer(game, layerElement));
  }
}

MapLayer::MapLayer(Game* game, TiXmlElement* layerElement):_stub(game->getStub()) {
  _tileSheet = game->getRessources()->getTileSheet(layerElement->Attribute("tilepath"));
  cout << "\t\tRead MapLayer id:"<<layerElement->Attribute("id");
  int firstW=0;
  for(TiXmlElement* row=layerElement->FirstChildElement("row");row;row=row->NextSiblingElement()) {
    const char* rowContent = row->FirstChild()->Value();
    int l = strlen(rowContent)/2;
    if(firstW==0)
      firstW=l;
    if(l!=firstW)
      throw new SystemException("Bad row content size. Should be %s",firstW);
    _rows.push_back(rowContent);
  }
  _w=firstW;
  _h=_rows.size();
  cout << " ("<<_w<<"x"<<_h<<")"<<endl;

}

void Map::draw(Rect *blit) {
	for (uint l=0; l<_layers.size(); l++) {
    _layers[l]->draw(blit);
  }
}

void MapLayer::draw(Rect *blit) {
  int surfId = _tileSheet->surfId;
  Rect dst;
  dst.x=dst.y=0;

	for (uint r=0; r<_rows.size(); r++) {
    string rowContent=_rows[r];
    dst.x=0;
    for (uint c=0; c<rowContent.size(); c+=2) {
      int tile = atoi(rowContent.substr(c, 2).c_str());
      if(tile<=0) continue;
      Frame* f = _tileSheet->tiles[tile];
      dst.w=f->loc.w;
      dst.h=f->loc.h;
      dst.y=r*f->loc.h;
      dst.x=(c/2)*f->loc.w;
      _stub->drawImage(surfId, &f->loc, &dst);
    }
  }
}

