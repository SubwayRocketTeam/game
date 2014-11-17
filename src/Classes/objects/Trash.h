#pragma once

#include "Unit.h"

#include <map>

class Trash : public Unit{
public:
	static Trash *create();

protected:
	Trash();
	virtual ~Trash();

	virtual bool init();
};
