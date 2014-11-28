#pragma once

class IterLock{
public:
	IterLock();

	void lock();
	void unlock();

	bool isLocked();
	bool isMarked();
	
	void markForRemove();
	void unmark();

private:
	bool locked;
	bool removed;
};