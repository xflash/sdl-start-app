#include "systemstub.h"
#include "Game.h"

int main(int argc, char *argv[]) {
	SystemStub *stub = SystemStub_SDL_create();

  Game *g = new Game(stub, "datas");
	g->run();

  delete g;
	delete stub;

	return 0;
}
