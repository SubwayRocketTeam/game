#include "JsonLoader.h"

using namespace std;

static JsonLoader *instance = nullptr;

JsonLoader *JsonLoader::create(){
	instance = new JsonLoader();

	if(instance)
		return instance;

	delete instance;
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

	_ASSERT(isCached(path) == false);

	/*
	auto file = FileUtils::getInstance();
	ssize_t fileSize;
	Json::Reader reader;
	Json::Value root;

	char *jsonData = 
		(char*)file->getFileData(path, "r", &fileSize);
	if(jsonData == nullptr)
		return false;

	jsonData[fileSize] = '\0';
	*/
	Json::Reader reader;
	Json::Value root;
	char *jsonData;
	size_t size;
	FILE *fp;

	fopen_s(&fp, path.c_str(), "r");
	if(fp == nullptr)
		return false;

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	jsonData = (char*)malloc(size);
	fread(jsonData, 1, size, fp);

	fclose(fp);

	if(!reader.parse(jsonData, root))
		return false;

	cache[path] = root;

	return true;
}
bool JsonLoader::loadFromCache(
	const string &path,
	Json::Value &root){

	_ASSERT(isCached(path) == true);

	root = cache[path];

	return true;
}