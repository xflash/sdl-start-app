#include "resources.h"
#include "systemstub.h"
#include "tinyXML/tinyxml.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <set>
using namespace std;

Resources::Resources(SystemStub* stub) : _stub(stub) { 
}

void Resources::loadAll(string datadir, string filename) {

  ostringstream ostr;
  ostr << datadir << "/" << filename;

  cout << "Loading Resources from ("<<ostr.str()<<")" << endl;

  TiXmlDocument doc(ostr.str().c_str());
  bool loadOkay = doc.LoadFile();
  if (!loadOkay)
    throw new SystemException("Could not load test file '%s'. Error='%s'.", ostr.str().c_str(), doc.ErrorDesc() );

  TiXmlNode* root = doc.FirstChild("resources");
  assert(root);


  TiXmlNode* tileSheets=root->FirstChild("tilesheets");
  for(TiXmlElement* tileSheet=tileSheets->FirstChildElement();tileSheet;tileSheet=tileSheet->NextSiblingElement()) {
    TileSheet* ts = new TileSheet();
    ts->id=tileSheet->Attribute("id");
    cout << "\tParsing TileSheet id: " << ts->id << endl;
    string tsfilename;
    tsfilename += datadir + "/" + tileSheet->Attribute("filename");
    uint32 bg;
    sscanf(tileSheet->Attribute("bg"), "%x", &bg);
    ts->surfId = _stub->readSurface(tsfilename, bg);
    _tileSheets[ts->id]=ts;

    for(TiXmlElement* tile=tileSheet->FirstChildElement("tile");tile;tile=tile->NextSiblingElement()) {
      //<tile id="water" x="0" y="0" w="18" h="18"/>
      Frame* f = new Frame();
      f->loc.x=atoi(tile->Attribute("x"));
      f->loc.y=atoi(tile->Attribute("y"));
      f->loc.w=atoi(tile->Attribute("w"));
      f->loc.h=atoi(tile->Attribute("h"));
      ts->tiles.push_back(f);
      cout << "\t\t\tParsing Tile ("<<f->loc.x << "," <<f->loc.y << ") - ("<< f->loc.w<<"x"<<f->loc.h<<")"<< endl;
    }

    for(TiXmlElement* tileAnimation=tileSheet->FirstChildElement("tileanimation");tileAnimation;tileAnimation=tileAnimation->NextSiblingElement()) {
      TileAnimation* ta = new TileAnimation();
      ta->id=tileAnimation->Attribute("id");
      ts->tileAnimations[ta->id]=ta;
      cout << "\t\t\tParsing TileAnimation id: " << ta->id <<endl;
      for(TiXmlElement* frameset=tileAnimation->FirstChildElement("frameset");frameset;frameset=frameset->NextSiblingElement()) {
        FrameSet* fs = new FrameSet();
        fs->id=frameset->Attribute("id");
        ta->framesets[fs->id]=fs;
        cout << "\t\t\t\tParsing FrameSet id: " << fs->id <<endl;
        for(TiXmlElement* frame=frameset->FirstChildElement("frame");frame;frame=frame->NextSiblingElement()) {
          Frame* f = new Frame();
          f->loc.x=atoi(frame->Attribute("x"));
          f->loc.y=atoi(frame->Attribute("y"));
          f->loc.w=atoi(frame->Attribute("w"));
          f->loc.h=atoi(frame->Attribute("h"));
          fs->frames.push_back(f);
          cout << "\t\t\t\tParsing Frame ("<<f->loc.x << "," <<f->loc.y << ") - ("<< f->loc.w<<"x"<<f->loc.h<<")"<< endl;
        }
      }
    }
  }
}
  /*
  for(int id=0; i<Resources::MAX_ID; i++) {
    _resources[id]=loadResource(id);
    if(_resources[id]==NULL) 
      throw new SystemException("Unable to read resources");
  }
  */

/*
void* Resources:load(int id) {
  ostringstream ostr;
  ostr << "datas/" << i << ".xml";
  string xmlFileName = ostr.str()

		TiXmlDocument doc( "demotest.xml" );
		bool loadOkay = doc.LoadFile();


}
*/

void Resources::destroy() {
  
}

TileSheet* Resources::getTileSheet(string id) {
  return _tileSheets.find(id)->second;
}
