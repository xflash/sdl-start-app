#include <ctime>
#include "systemstub.h"
#include "game.h"
#include "Character.h"
#include "HumanPlayer.h"
#include "HumanSeeker.h"
#include "bullet.h"
#include <sstream>
#include <iostream>
#include "tinyXML/TinyXML.h"


Game::Game(SystemStub* stub, string datadir)
	: _stub(stub), _res(stub, datadir),_datadir(datadir) {
}

Character* Game::createCharacterFromXmlElement(TiXmlElement* character, CharacterUpdater* updater) {
  const char* id = character->Attribute("id");
  const char* tilepath = character->Attribute("tilepath");
  const char* dbg = character->Attribute("dbg");
  Character* c = new Character(_stub, updater);
  if(dbg!=NULL)
    c->_dbg=_stricmp("true", dbg)==0;
  c->init(&_res, tilepath);
  c->_loc.x=atoi(character->Attribute("x"));
  c->_loc.y=atoi(character->Attribute("y"));
  _characters[id]=c;

  return c;
}

void Game::init() {
	_stub->init("Test", GAMESCREEN_W, GAMESCREEN_H);
  _res.loadAll();

  ostringstream ostr;
  ostr << _datadir << "/" << "game.xml";
  cout << "Loading Game from ("<<ostr.str()<<")" << endl;

  string filename = ostr.str();
  TiXmlDocument doc(filename.c_str());
  if (!doc.LoadFile())
    throw new SystemException("Could not load test file '%s'. Error='%s'.", filename.c_str(), doc.ErrorDesc() );

  TiXmlNode* root = doc.FirstChild("game");
  assert(root);

  TiXmlElement* bullets=root->FirstChildElement("bullets");
  _bullets = new BulletPool();
  int nb = atoi(bullets->Attribute("nb"));
  const char* tilepath = bullets->Attribute("tilepath");
  _bullets->init(nb, &_res, _stub, this, tilepath);


  HumanSeeker* hs = new HumanSeeker(_stub, 70);
  HumanPlayer* hp=new HumanPlayer(&_stub->_pi, _bullets);

  TiXmlNode* player=root->FirstChild("player");
  TiXmlElement* playerCharacter = player->FirstChildElement("character");
  createCharacterFromXmlElement(playerCharacter, hp);

  TiXmlNode* characters=root->FirstChild("characters");
  for(TiXmlElement* character=characters->FirstChildElement();character;character=character->NextSiblingElement()) {
    createCharacterFromXmlElement(character, hs);
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

  IT_Characters it;
  for(it=_characters.begin(); it!=_characters.end(); ++it) {
	  (it->second)->update();
  }

  _bullets->move();
}

void Game::draw() {
  static Point locMsg;
  static Point locMouse;
  locMouse.x = _stub->_pi.mouseX;
  locMouse.y = _stub->_pi.mouseY;

  //_peon.draw();
  //_stub->drawLine(&_peon._loc, &locMouse);

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

  _stub->drawString(&locMsg, "Mouse: (%d,%d) %s", _stub->_pi.mouseX, _stub->_pi.mouseY, (_stub->_pi.click)?"Click":"");
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
