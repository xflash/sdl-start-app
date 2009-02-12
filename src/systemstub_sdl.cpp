#include <SDL.h>
#include <SDL_image.h>
#include "systemstub.h"
#include "resources.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

struct SystemStub_SDL : SystemStub {
  enum {
    SCREEN_BPP = 24,
  };
	SDL_Surface* _screen;
	map<uint8, SDL_Surface*> _surfaces;
  uint8 _surfaceCount;
	uint16 _screenW, _screenH;

	virtual ~SystemStub_SDL() {}
	virtual void init(const char *title, uint16 w, uint16 h);
	virtual void destroy();
	virtual void processEvents();
	virtual void sleep(uint32 duration);
  virtual void updateScreen();
  virtual uint32 getTimeStamp();
  virtual void drawImage(uint8 resId, int16 x, int16 y);
  virtual void drawImage(uint8 resId, Rect* srcImg, Point* dstRect);
  virtual uint8 readSurface(string filename, uint32 bgColor);

};

SystemStub *SystemStub_SDL_create() {
	return new SystemStub_SDL();
}

void SystemStub_SDL::init(const char *title, uint16 w, uint16 h) {
	SDL_Init(SDL_INIT_VIDEO);
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_SetCaption(title, NULL);
	memset(&_pi, 0, sizeof(_pi));
	_screenW = w;
	_screenH = h;
  _screen = SDL_SetVideoMode(w, h, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (!_screen)
		throw new SystemException("SystemStub_SDL Unable to allocate _screen buffer");
	
  _surfaceCount=0;
}
void SystemStub_SDL::destroy() {
/*
if (_resources) {
    for(int i=0; i<Resources::MAX_ID; i++) {
  		SDL_FreeSurface(_resources[i]);
    }

    delete[] _resources;
		_resources = 0;
	}
*/
  if (_screen) {
		// freed by SDL_Quit()
		_screen = 0;
	}
	SDL_Quit();
}

void SystemStub_SDL::updateScreen() {
  SDL_Flip(_screen);
  SDL_FillRect(_screen, &_screen->clip_rect, SDL_MapRGB(_screen->format, 0xF0, 0xf0, 0xf0) ); 
}

void SystemStub_SDL::processEvents() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_QUIT:
			_pi.quit = true;
			break;
		case SDL_KEYUP:
			switch (ev.key.keysym.sym) {
			case SDLK_LEFT:
				_pi.dirMask &= ~PlayerInput::DIR_LEFT;
				break;
			case SDLK_RIGHT:
				_pi.dirMask &= ~PlayerInput::DIR_RIGHT;
				break;
			case SDLK_UP:
				_pi.dirMask &= ~PlayerInput::DIR_UP;
				break;
			case SDLK_DOWN:
				_pi.dirMask &= ~PlayerInput::DIR_DOWN;
				break;
			case SDLK_SPACE:
				_pi.space = false;
				break;
      case SDLK_TAB:
        _pi.dbgMask &= ~PlayerInput::DF_FASTMODE;
        break;
			case SDLK_ESCAPE:
				_pi.escape = false;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYDOWN:
			_pi.lastChar = ev.key.keysym.sym;
			switch (ev.key.keysym.sym) {
			case SDLK_LEFT:
				_pi.dirMask |= PlayerInput::DIR_LEFT;
				break;
			case SDLK_RIGHT:
				_pi.dirMask |= PlayerInput::DIR_RIGHT;
				break;
			case SDLK_UP:
				_pi.dirMask |= PlayerInput::DIR_UP;
				break;
			case SDLK_DOWN:
				_pi.dirMask |= PlayerInput::DIR_DOWN;
				break;
      case SDLK_TAB:
        _pi.dbgMask |= PlayerInput::DF_FASTMODE;
        break;
			case SDLK_SPACE:
				_pi.space = true;
				break;
			case SDLK_ESCAPE:
				_pi.escape = true;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}


void SystemStub_SDL::sleep(uint32 duration) {
	SDL_Delay(duration);
}

uint32 SystemStub_SDL::getTimeStamp() {
	return SDL_GetTicks();
}

void SystemStub_SDL::drawImage(uint8 resId, int16 x, int16 y) {
  Point p; p.x=x; p.y=y;
  drawImage(resId, NULL, &p);
}

void SystemStub_SDL::drawImage(uint8 resId, Rect* srcImg, Point* dstRect) {
  SDL_Surface* surfToBlit=_surfaces[resId];
    SDL_Rect blitSrc;
    SDL_Rect blitDst;
    blitDst.x=dstRect->x; blitDst.y=dstRect->y;

    if(srcImg!=NULL) {
      blitSrc.x=srcImg->x; blitSrc.y=srcImg->y;
      blitSrc.w=srcImg->w; blitSrc.h=srcImg->h;
      blitDst.w=srcImg->w; blitDst.h=srcImg->h;
      SDL_BlitSurface(surfToBlit, &blitSrc, _screen, &blitDst);
    } else {
      SDL_BlitSurface(surfToBlit, NULL, _screen, &blitDst);
    }

}

uint8 SystemStub_SDL::readSurface(string filename, uint32 bgColor) {
  cout << "Loading Surface from ("<<filename<<") - ";
  SDL_Surface* loadedImage=IMG_Load(filename.c_str());
  if(loadedImage!=NULL) { 
    SDL_Surface* optimized=SDL_DisplayFormat(loadedImage);
    SDL_SetColorKey(optimized, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimized->format, (bgColor>>16)&0x0000FF, (bgColor>>8)&0x00FF, (bgColor)&0xFF));
    cout << "OK : size (" << loadedImage->w << "x" << loadedImage->h << ")" << endl;
    SDL_FreeSurface(loadedImage);
    _surfaces[_surfaceCount]=optimized;
    uint8 res=_surfaceCount;
    _surfaceCount++;
    return res;
  }
  cout << "NOK" << endl;
  throw new SystemException("Unable to read Surface from %s",filename.c_str());
}