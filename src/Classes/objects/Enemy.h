#pragma once

#include "Unit.h"

class Enemy : public Unit{
public:
	static Enemy *create();
	
    virtual bool init();

	void focus();
	void unfocus();

protected:
	Enemy();
	virtual ~Enemy();

	virtual bool initPhysics();
};
