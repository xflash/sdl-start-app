#include "blittable.h"
#include "systemstub.h"

Blittable::Blittable(SystemStub* stub):_stub(stub) { 
}

void Blittable::draw(Frame* fr, Point* loc) {

  _blitter.x=fr->loc.x;
  _blitter.y=fr->loc.y;
  _blitter.w=fr->loc.w;
  _blitter.h=fr->loc.h;

  _stub->drawImage(_surfId, &_blitter, loc);
}

