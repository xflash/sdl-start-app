#ifndef __ACTORPOOL_H__
#define __ACTORPOOL_H__

#include "intern.h"
#include "actor.h"
#include <vector>
using namespace std;

template<class T>  class ActorPool {

public:
	vector<T*> actor;
protected:
	int actorIdx;
private:
  bool hasNoActor;
	
public:
	ActorPool() { 
	  actorIdx = 0; 
    hasNoActor = false;
  }
	
	ActorPool(int n, InitActorArgs* args = NULL) { 
	  createActors(n, args); 
	}

  void createActors(int n, InitActorArgs* args = NULL) { 
		//actor.resize(n);
		for(int i=0; i<n; i++){
			T* t = new T;
			actor.push_back(t);
//			t->exists (false);
			t->init(args);
		}
		actorIdx = 0;
    hasNoActor = false;
	}

	T* getInstance() {
    if (hasNoActor)
      return 0;
		for (unsigned int i = 0; i < actor.size(); i++) {
			actorIdx--;
			if (actorIdx < 0)
				actorIdx = (int)actor.size() - 1;
			if (!actor[actorIdx]->exists())  {
			  actor[actorIdx]->exists(true);
				return actor[actorIdx];
			}
		}
    hasNoActor = true;
		return 0;
	}
	
	T* getInstanceForced() {
		actorIdx--;
		if (actorIdx < 0)
			actorIdx = actor.size() - 1;
		return actor[actorIdx];
	}
	
	void move() {
    hasNoActor = false;
		for (unsigned int i = 0; i < actor.size(); i++) {
			T* act=actor[i];
			if (act->exists()) 
				act->move();
		}
	}
	
	void draw() {
		for (unsigned int i = 0; i < actor.size(); i++) {
			T* act=actor[i];
			if (act->exists()) 
				act->draw();
		}
	}
	
	void clear() {
		for (unsigned int i = 0; i < actor.size(); i++) {
			actor[i]->exists(false);
		}
		actorIdx = 0;
	}

	unsigned int getNumMax() {	
		return actor.size();
	}
	
	unsigned int getIndex() { return actorIdx; }
	
	unsigned int getNum() {
		unsigned int num = 0;
		for (unsigned int i = 0; i < actor.size(); i++) {
			if (actor[i]->exists()) 
				num++;
		}
		return num;
	}
	
};

#endif // __ACTORPOOL_H__

