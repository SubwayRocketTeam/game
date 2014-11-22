#include "pch.h"
#include "JsonLoader.h"

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

static JsonLoader *instance = nullptr;

JsonLoader *JsonLoader::create(){
	instance = new JsonLoader();

	if(instance)
		return instance;

	CC_SAFE_DELETE(instance);
	return nullptr;
}
JsonLoader *JsonLoader::getInstance(){
	return instance;
}
bool JsonLoader::load(
	const string &path, Json::Value &root){

	auto loader = JsonLoader::getInstance();

	return loader->loadFromFile(path, root);
}

bool JsonLoader::loadFromFile(
	const string &path, Json::Value &root){

	if(!isCached(path))
		loadToCache(path);

	return loadFromCache(path, root);
}

bool JsonLoader::isCached(
	const string &path){

	return !(cache.find(path) == cache.end());
}
bool JsonLoader::loadToCache(
	const string &path){

	CC_ASSERT(isCached(path) == false);

	auto file = FileUtils::getInstance();
	ssize_t fileSize;
	Json::Reader reader;
	Json::Value root;

	char *jsonData = 
		(char*)file->getFileData(path, "r", &fileSize);
	if(jsonData == nullptr)
		return false;

	jsonData[fileSize] = '\0';

	if(!reader.parse(jsonData, root))
		return false;

	cache[path] = root;

	cocos2d::log(
		"cached - %s", path.c_str());

	return true;
}
bool JsonLoader::loadFromCache(
	const string &path,
	Json::Value &root){

	CC_ASSERT(isCached(path) == true);

	root = cache[path];

	return true;
}