#pragma once

#include "Unit.h"

class Stage;

class RepairArea : public Unit{
public:
	RepairArea();
	virtual ~RepairArea();

	virtual bool init();
	virtual void update(float dt);
};
