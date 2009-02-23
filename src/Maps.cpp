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
    _maps[mapElement->Attribute("id")] = new Map(game, mapElement);
  }
}

Map* Maps::getMap(string mapId) {
  return _maps[mapId];
}

Map::Map(Game* game, TiXmlElement* mapElement) {
  cout << "\tRead Map id:"<<mapElement->Attribute("id") << endl;
  _tileSheet = game->getRessources()->getTileSheet(mapElement->Attribute("tilepath"));
  TiXmlElement* tilesElement = mapElement->FirstChildElement("tiles");
  for(TiXmlElement* tileElement=tilesElement->FirstChildElement("tile");tileElement;tileElement=tileElement->NextSiblingElement()) {
    _tiles.push_back(new MapTile(game, _tileSheet, tileElement));
  }
  TiXmlElement* layersElement = mapElement->FirstChildElement("layers");
  for(TiXmlElement* layerElement=layersElement->FirstChildElement("layer");layerElement;layerElement=layerElement->NextSiblingElement()) {
    _layers.push_back(new MapLayer(layerElement));
  }
}

MapTile::MapTile(Game* game, TileSheet* tileSheet, TiXmlElement* layerElement) {
  cout << "\t\tRead MapTile " << endl;

  const char* residx = layerElement->Attribute("residx");
  _resFrame =NULL;
  if(NULL!=residx) 
    _resFrame = tileSheet->tiles[atoi(residx)];
   
  const char* coll = layerElement->Attribute("coll");
  _collision=false;
  if(NULL!=coll) 
    _collision=_stricmp("true", coll)==0;
}

MapLayer::MapLayer(TiXmlElement* layerElement) {
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



/** Drawings **/

void Map::draw(SystemStub* stub, Rect *blit) {
	for (uint l=0; l<_layers.size(); l++) {
    _layers[l]->draw(stub, blit, _tileSheet->surfId, &_tiles);
  }
}

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

