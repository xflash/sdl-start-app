#ifndef __SYSTEMSTUB_H__
#define __SYSTEMSTUB_H__

#include "intern.h"

struct PlayerInput {
	enum {
		DIR_UP    = 1 << 0,
		DIR_DOWN  = 1 << 1,
		DIR_LEFT  = 1 << 2,
		DIR_RIGHT = 1 << 3
	};
  enum {
    DF_FASTMODE  = 1 << 0,
  };

	uint8 dirMask;
  uint8 dbgMask;
	bool space;
	char lastChar;
	bool quit;
};

struct SystemException {
  SystemException(const char* msg) {}
};

struct SystemStub {
	PlayerInput _pi;

	virtual ~SystemStub() {}

	virtual void init(const char *title, uint16 w, uint16 h) = 0;
	virtual void destroy() = 0;

	virtual void processEvents() = 0;
	virtual void sleep(uint32 duration) = 0;
  virtual void updateScreen() = 0;
  virtual uint32 getTimeStamp() = 0;

  virtual void draw(uint8 resId, int16 x, int16 y) = 0;

};

extern SystemStub *SystemStub_SDL_create();
//extern SystemStub *SystemStub_Win32_create();

#endif // __SYSTEMSTUB_H__
