#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "intern.h"
#include <vector>
using namespace std;

typedef vector<void*> InitActorArgs;
	
class Actor {
private:
  bool _exists;

public:
	Actor():_exists(false) { }
	virtual ~Actor() { }
	inline bool exists() { return _exists; }
	inline void exists(bool value) { 
		(value)?activate():desactivate();
		_exists = value; 
	}
   
protected:
	virtual void activate() {}
	virtual void desactivate() {}
public:
	virtual void init(InitActorArgs* args)=0;
	virtual void move()=0;
	virtual void draw()=0;
};

#endif //__ACTOR_H__
