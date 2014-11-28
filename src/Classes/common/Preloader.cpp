#include "pch.h"
#include "Preloader.h"

#include "audio/include/SimpleAudioEngine.h"

#include <vector>

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

#define _BRANCHED_CALL(prefix ,type, name) switch(type){ \
	case ResourceType::BGM: \
		prefix##BGM(name); \
		break; \
	case ResourceType::SoundEffect: \
		prefix##SoundEffect(name); \
		break; \
	case ResourceType::Plist: \
		prefix##Plist(name); \
		break; \
	};

struct Preloader::Transaction{
	vector<string> bgms;
	vector<string> effects;
	vector<string> plists;
};
struct Preloader::ResourceData{
	ResourceType type;
	string name;
	int ref;
};

static Preloader *instance = nullptr;

Preloader::Preloader(){
}
Preloader::~Preloader(){
}

Preloader *Preloader::create(){
	auto p = new Preloader();

	if(p) return p;
	CC_SAFE_DELETE(p);
	return nullptr;
}
Preloader *Preloader::getInstance(){
	return instance;
}

bool Preloader::push(
	const string &name){

	return true;
}
void Preloader::pop(
	const string &name){
}

void Preloader::loadBGM(
	const string &name){

	/* DO NOTHING */
}
void Preloader::loadSoundEffect(
	const string &name){

	SimpleAudioEngine::getInstance()
		->preloadEffect(name.c_str());
}
void Preloader::loadPlist(
	const string &name){

	SpriteFrameCache::getInstance()
		->addSpriteFramesWithFile(name);
}
void Preloader::unloadBGM(
	const string &name){

	/* DO NOTHING */
}
void Preloader::unloadSoundEffect(
	const string &name){

	SimpleAudioEngine::getInstance()
		->unloadEffect(name.c_str());
}
void Preloader::unloadPlist(
	const string &name){

	SpriteFrameCache::getInstance()
		->removeSpriteFramesFromFile(name);
}

void Preloader::load(
	ResourceType type,
	const string &name){

	auto &pair = resources.find(name);

	/* LOAD */
	if(pair == resources.end()){
		_BRANCHED_CALL(load, type, name);

		auto &data = resources[name];
		data.name = name;
		data.type = type;
		data.ref = 1;
	}
	else
		pair->second.ref ++;
}
void Preloader::unload(
	ResourceType type,
	const string &name){

	CC_ASSERT(resources.find(name) != resources.end());

	auto &data = resources[name];
	data.ref --;

	/* RELEASE */
	if(data.ref == 0){
		_BRANCHED_CALL(load, type, name);

		resources.erase(name);
	}
}