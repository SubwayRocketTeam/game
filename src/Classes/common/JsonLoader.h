#pragma once

#include "json/json.h"

#include <string>
#include <map>

class JsonLoader{
public:
	static JsonLoader *create();
	static JsonLoader *getInstance();
	static bool load(
		const std::string &path, 
		Json::Value &root);

	bool loadFromFile(
		const std::string &path, 
		Json::Value &root);

protected:
	bool isCached(
		const std::string &path);
	bool loadToCache(
		const std::string &path);
	bool loadFromCache(
		const std::string &path,
		Json::Value &root);

private:
	std::map<std::string,Json::Value> cache;
};