#include "Maps.h"
#include "tinyXML/TinyXML.h"
#include <iostream>
#include <sstream>

Maps::Maps(void) {

}

Maps::~Maps(void) {
}

void Maps::loadAll(string datadir, string filename) {
  ostringstream ostr;
  ostr << datadir << "/" << filename;
  cout << "Loading Maps from ("<<ostr.str()<<")" << endl;

  TiXmlDocument doc(ostr.str().c_str());
  if (!doc.LoadFile())
    throw new SystemException("Could not load test file '%s'. Error='%s'.", filename.c_str(), doc.ErrorDesc() );

  TiXmlNode* root = doc.FirstChild("maps");
  assert(root);
}
