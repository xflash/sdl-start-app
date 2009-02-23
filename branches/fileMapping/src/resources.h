#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "intern.h"
#include <map>
#include <string>
using namespace std;

class SystemStub;

class Resources {
private:
  SystemStub* _stub;
  map<string, TileSheet*> _tileSheets;

public:
  Resources (SystemStub* stub);
  TileSheet* getTileSheet(string id);

  void loadAll(string datadir, string filename);
  void destroy();
};

#endif // __RESOURCES_H__
