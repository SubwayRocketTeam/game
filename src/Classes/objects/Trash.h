
#pragma once

#include "Unit.h"

class Trash : public Unit{
public:
	static Trash *create();

	void sweep();

protected:
	Trash();
	virtual ~Trash();

	virtual bool init();
};
