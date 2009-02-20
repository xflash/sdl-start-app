#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "intern.h"

class SystemStub;
class Resources;
class CharacterUpdater;
class TiXmlElement;
class Game;

class Character{
private:
  CharacterUpdater* _updater;
  FrameSet* _upSet;
  FrameSet* _downSet;
  FrameSet* _leftSet;
  FrameSet* _rightSet;
  FrameSet* _frameSet;
  uint _frame;
  bool _animated;

  bool _dbg;
  SystemStub* _stub;
  Point _loc;
  Rect _bbox;
  int16 _xd;
  int16 _yd;
  Rect  _frameBlitter;
  Rect  _dstBlitter;
  uint8 _surfId;
  string _tilename;

public:
  enum {
    ACC_X=  5,
    ACC_Y=  3,
  };


  Character(Game* game, CharacterUpdater* updater, TiXmlElement* elementCharacter);
  

  void update();
  void updateInput();
  void draw();

  Rect* getBBox() { return &_bbox; }

  void moveLeft();
  void moveRight();
  void stopX();
  void moveUp();
  void moveDown();
  void stopY();
  void checkStop();

};

#endif // __CHARACTER_H__
