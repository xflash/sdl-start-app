#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "intern.h"
#include <map>
#include <string>
using namespace std;

class SystemStub;

class Resources {
public:
  SystemStub* _stub;
  map<string, TileSheet*> _tileSheets;
  string _datadir;

  Resources (SystemStub* stub, string datadir);

  void loadAll();
  void readFileContent(string filename, void** readedContent, long* readedSize);

  void destroy();
};

#endif // __RESOURCES_H__
