#include <ctime>
#include "systemstub.h"
#include "Game.h"
#include "Character.h"
#include "HumanPlayer.h"
#include "HumanSeeker.h"
#include "bullet.h"
#include "Maps.h"
#include <sstream>
#include <iostream>
#include "tinyXML/TinyXML.h"

#define DEFAULT_RESOURCES_XML_FILENAME "resources.xml"
#define DEFAULT_GAME_XML_FILENAME "game.xml"
#define DEFAULT_MAPS_XML_FILENAME "maps.xml"

Game::Game(SystemStub* stub, string datadir)
	: _stub(stub), _res(stub), _datadir(datadir) {
}

void Game::init() {
	_stub->init("Test", GAMESCREEN_W, GAMESCREEN_H);

  _res.loadAll(_datadir, DEFAULT_RESOURCES_XML_FILENAME);

  _maps = new Maps(this);
  _maps->loadAll(_datadir, DEFAULT_MAPS_XML_FILENAME);

  ostringstream ostr;
  ostr << _datadir << "/" << DEFAULT_GAME_XML_FILENAME;
  cout << "Loading Game from ("<<ostr.str()<<")" << endl;
  TiXmlDocument doc(ostr.str().c_str());
  if (!doc.LoadFile())
    throw new SystemException("Could not load test file '%s'. Error='%s'.", ostr.str().c_str(), doc.ErrorDesc() );

  TiXmlNode* root = doc.FirstChild("game");
  assert(root);

  TiXmlElement* mapElement=root->FirstChildElement("map");
  _map = _maps->getMap(mapElement->Attribute("mapid"));

  _bullets = new BulletPool(this, root->FirstChildElement("bullets"));

  TiXmlNode* player=root->FirstChild("player");
  HumanPlayer* hp=new HumanPlayer(&_stub->_pi, _bullets);
  TiXmlElement* playerCharacter = player->FirstChildElement("character");
  _characters[playerCharacter->Attribute("id")]=new Character(this, hp, playerCharacter);

  TiXmlNode* characters=root->FirstChild("characters");
  for(TiXmlElement* character=characters->FirstChildElement();character;character=character->NextSiblingElement()) {
    TiXmlElement* updater=character->FirstChildElement("humanSeeker");
    CharacterUpdater* hs = NULL;
    if(updater!=NULL) {
      hs = new HumanSeeker(this, updater);
    }
    _characters[character->Attribute("id")]=new Character(this, hs, character);
  }
}

void Game::close() {
	_stub->destroy();
}

void Game::run() {
  init();
  mainLoop();
  close();
}

void Game::mainLoop() {
  while (!_stub->_pi.quit) {
  	_stub->processEvents();
    if(_stub->_pi.escape) break;
    move();
    draw();
    _stub->updateScreen();
	}
}

void Game::move() {

  _mapBlit.x=_mapBlit.y=_mapBlit.w=_mapBlit.h=0;

  IT_Characters it;
  for(it=_characters.begin(); it!=_characters.end(); ++it) {
	  (it->second)->update();
  }

  _bullets->move();
}

void Game::draw() {
  static Point locMsg;

  //_peon.draw();
  //_stub->drawLine(&_peon._loc, &locMouse);

  _map->draw(&_mapBlit);

  IT_Characters it;
  for(it=_characters.begin(); it!=_characters.end(); ++it) {
	  Character* act=it->second;
	  (it->second)->draw();
  }
  
  _bullets->draw();

  locMsg.y=locMsg.x=0;
  static int msgRowSize=10;

  uint32 delay = updateTiming();
  _stub->drawString(&locMsg, "FrameTime: %d ms",delay);
  locMsg.y+=msgRowSize;

  _stub->drawString(&locMsg, "Bullets: %d/%d",_bullets->getNum(), _bullets->getNumMax());
  locMsg.y+=msgRowSize;

  _stub->drawString(&locMsg, "Mouse: (%d,%d) %s", _stub->_pi.mouse.x, _stub->_pi.mouse.y, (_stub->_pi.click)?"Click":"");
  locMsg.y+=msgRowSize;
}

uint32 Game::updateTiming() {
	static uint32 tstamp = 0;
	int32 delay = _stub->getTimeStamp() - tstamp;
	int32 pause = (_stub->_pi.dbgMask & PlayerInput::DF_FASTMODE) ? 20 : 30;
	pause -= delay;
	if (pause > 0) {
		_stub->sleep(pause);
	}
	tstamp = _stub->getTimeStamp();
  return delay;
}
