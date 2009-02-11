#include "systemstub.h"
#include "game.h"

int main(int argc, char *argv[]) {
	SystemStub *stub = SystemStub_SDL_create();

  Game *g = new Game(stub);
	g->run();

  delete g;
	delete stub;

	return 0;
}
