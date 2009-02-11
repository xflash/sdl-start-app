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
    SCREEN_BPP = 32,
  };
	SDL_Surface* _screen;
	SDL_Surface** _resources;
	uint16 _screenW, _screenH;

  SDL_Surface* loadImage(string filename);

	virtual ~SystemStub_SDL() {}
	virtual void init(const char *title, uint16 w, uint16 h);
	virtual void destroy();
	virtual void processEvents();
	virtual void sleep(uint32 duration);
  virtual void updateScreen();
  virtual uint32 getTimeStamp();
  virtual void draw(uint8 resId, int16 x, int16 y);
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
	
	const SDL_PixelFormat *pf = _screen->format;

  _resources = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*Resources::MAX_ID);
  cout << "Loading Images ("<<Resources::MAX_ID<<")" << endl;
  for(int i=0; i<Resources::MAX_ID; i++) {
    ostringstream ostr;
    ostr << "datas/" << i << ".png";
    _resources[i]=loadImage(ostr.str());
    if(_resources[i]==NULL) 
      throw new SystemException("Unable to read resources");
  }
}

SDL_Surface* SystemStub_SDL::loadImage(string filename) {
  cout << "\t<" << filename << "> - " ;
  SDL_Surface* loadedImage=IMG_Load(filename.c_str());
  if(loadedImage!=NULL) { 
    SDL_Surface* optimized=SDL_DisplayFormat(loadedImage);
    SDL_SetColorKey(optimized, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimized->format, 0xFF, 0x00, 0xFF));
    cout << "OK : size (" << loadedImage->w << "x" << loadedImage->h << ")" << endl;
    SDL_FreeSurface(loadedImage);
    return optimized;
  }
  cout << "NOK" << endl;
  return NULL;
}

void SystemStub_SDL::destroy() {
	if (_resources) {
    for(int i=0; i<Resources::MAX_ID; i++) {
  		SDL_FreeSurface(_resources[i]);
    }

    delete[] _resources;
		_resources = 0;
	}
	if (_screen) {
		// freed by SDL_Quit()
		_screen = 0;
	}
	SDL_Quit();
}

void SystemStub_SDL::updateScreen() {
  SDL_Flip(_screen);
  SDL_FillRect(_screen, &_screen->clip_rect, SDL_MapRGB(_screen->format, 0x00, 0x00, 0x00) ); 
  //SDL_UpdateRect(_screen, 0,0, _screenW, _screenH);
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

void SystemStub_SDL::draw(uint8 resId, int16 x, int16 y) {
  //cout << "Blit "<<resId<<" at ("<<x<<","<<y<<")"<<endl;
    SDL_Surface* surfToBlit=_resources[resId];
    SDL_Rect blitSrc;
    blitSrc.x=0; blitSrc.y=0;
    blitSrc.w=surfToBlit->w; blitSrc.h=surfToBlit->h;
    SDL_Rect blitDst;
    blitDst.x=x; blitDst.y=y;
    blitDst.w=surfToBlit->w; blitDst.h=surfToBlit->h;
    SDL_BlitSurface(surfToBlit, &blitSrc, _screen, &blitDst);
}