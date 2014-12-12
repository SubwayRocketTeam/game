#pragma once

#include <atomic>

class Ref{
	typedef std::atomic<int> counter_t;

	Ref() : refCount(0) {};
	virtual ~Ref(){};

	void retain(){
		refCount++;
	}
	void release(){
		refCount--;

		if(refCount == 0)
			delete this;
	}

private:
	counter_t refCount;
};