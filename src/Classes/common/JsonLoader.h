#pragma once

#include "json/json.h"

#include <string>

class JsonLoader{
public:
	static bool load(
		const std::string &path, 
		Json::Value &root);
};