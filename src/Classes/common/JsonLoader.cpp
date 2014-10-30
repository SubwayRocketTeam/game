#include "JsonLoader.h"

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

bool JsonLoader::load(
	const string &path, Json::Value &root){

	auto file = FileUtils::getInstance();
	ssize_t fileSize;
	Json::Reader reader;
	
	char *jsonData = 
		(char*)file->getFileData(path, "r", &fileSize);
	if(jsonData == nullptr)
		return false;

	jsonData[fileSize] = '\0';

	if(!reader.parse(jsonData, root))
		return false;

	return true;
}