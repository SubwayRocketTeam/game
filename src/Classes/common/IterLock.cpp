#include "pch.h"
#include "IterLock.h"

#include "cocos2d.h"

IterLock::IterLock() :
	locked(false), removed(false){
}

void IterLock::lock(){
	CC_ASSERT(locked == false);

	locked = true;
}
void IterLock::unlock(){
	CC_ASSERT(locked == true);

	locked = false;
}

bool IterLock::isLocked(){
	return locked;
}
bool IterLock::isMarked(){
	return remove;
}

void IterLock::markForRemove(){
	removed = true;
}
void IterLock::unmark(){
	removed = false;
}