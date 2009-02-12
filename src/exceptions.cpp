#include "exceptions.h"
#include <cstdarg>
#include <cstdio>

static char buf[1024];

SystemException::SystemException(string msg, ...) {
  va_list va;
  va_start(va, msg);
  vsprintf(buf, msg.c_str(), va);
  va_end(va);
  _msg = buf;
}