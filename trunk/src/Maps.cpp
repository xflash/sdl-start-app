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
  _w = atoi(mapElement->Attribute("w"));
  _h = atoi(mapElement->Attribute("h"));
  _tileSheet = game->getRessources()->getTileSheet(mapElement->Attribute("tilepath"));

  cout << "\tRead Map id:"<<mapElement->Attribute("id")<< " ("<<_w<<"x"<<_h<<")"<<endl;

  for(TiXmlElement* row=mapElement->FirstChildElement("row");row;row=row->NextSiblingElement()) {
    const char* rowContent = row->FirstChild()->Value();
    if(strlen(rowContent)!=_w)
      throw new SystemException("Bad row content size");
    _rows.push_back(rowContent);
  }
  if(_rows.size()!=_h) {
    throw new SystemException("Bad row number");
  }
}

void Map::draw(Rect *blit) {
  int surfId = _tileSheet->surfId;
  Rect dst;
  dst.x=dst.y=0;

	for (uint r=0; r<_rows.size(); r++) {
    string rowContent=_rows[r];
    dst.x=0;
    for (uint c=0; c<rowContent.size(); c++) {
      int tile = atoi(rowContent.substr(c, 1).c_str());
      Frame* f = _tileSheet->tiles[tile];
      dst.w=f->loc.w;
      dst.h=f->loc.h;
      dst.y=r*f->loc.h;
      _stub->drawImage(surfId, &f->loc, &dst);
      dst.x=c*f->loc.w;
    }
  }
}