#pragma once

#define INVALID_ID 0

typedef unsigned int id_t;

class IDDispenser {
public:
	IDDispenser() :nextId(0) {
	}

	id_t issue() {
		return ++nextId;
	}

private:
	id_t nextId;
};