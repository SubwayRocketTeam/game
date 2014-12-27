#pragma once

#include "Unit.h"

class Stage;

class RepairArea : public Unit{
public:
	RepairArea(Stage* const stage);
	virtual ~RepairArea();

	virtual bool init();
	virtual void update(float dt);

public:
	Stage* const stage;

};
