#pragma once

#include "Unit.h"

#include <set>

class RepairArea : public Unit{
public:
	static RepairArea *create();

protected:
	RepairArea();
	virtual ~RepairArea();

	virtual bool init();

};
