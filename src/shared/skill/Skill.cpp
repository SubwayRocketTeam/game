#include "Skill.h"

#include "shared/JsonLoader.h"

using namespace std;

bool Skill::init(
	const string &dataPath){

	if(!initExternalData(dataPath))
		return false;

	return true;
}
bool Skill::initExternalData(
	const string &dataPath){

	if(!JsonLoader::load(dataPath, json))
		return false;

	id = json.get("id", -1).asInt();
	if(id == -1) return false;

	tooltip = json.get("tooltip", "").asString();
	if(tooltip.empty()) return false;

	name = json.get("name", "").asString();
	if(name.empty()) return false;

	duration = json.get("duration",0).asFloat();

	return true;
}