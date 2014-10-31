#include "Skill.h"

#include "common/JsonLoader.h"

using namespace std;
using namespace cocos2d;

int Skill::id = -1;
string Skill::tooltip;
string Skill::name;

bool Skill::init(
	const string &dataPath){

	if(!initExternalData(dataPath))
		return false;

	return true;
}
bool Skill::initExternalData(
	const string &dataPath){

	Json::Value root;
	if(!JsonLoader::load(dataPath, root))
		return false;

	id = root.get("id", -1).asInt();
	if(id == -1) return false;

	tooltip = root.get("tooltip", "").asString();
	if(tooltip.empty()) return false;

	name = root.get("name", "").asString();
	if(name.empty()) return false;

	return true;
}