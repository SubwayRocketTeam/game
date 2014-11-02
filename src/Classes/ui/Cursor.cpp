#include "Cursor.h"

Cursor* Cursor::instance = nullptr;

Cursor::Cursor() {

}

Cursor::~Cursor() {

}

Cursor* Cursor::create() {
	Cursor* cursor = new Cursor();

	if (cursor && cursor->init()) {
		cursor->autorelease();
		return cursor;
	}
	else {
		delete cursor;
		cursor = nullptr;
		return cursor;
	}
}

Cursor* Cursor::getInstance() {
	return getInstance("");
}

Cursor* Cursor::getInstance(const char* filename) {
	if (!instance) {
		instance = Cursor::create();
	}
	instance->initWithFile(filename);
	return instance;
}

void Cursor::update(float dt) {

}