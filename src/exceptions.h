#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include "intern.h"
#include <string>
using namespace std;

struct SystemException {
  string _msg;
  SystemException(string msg, ...);
};



#endif // __EXCEPTIONS_H__
