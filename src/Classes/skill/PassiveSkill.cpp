#include "pch.h"
#include "PassiveSkill.h"

using namespace std;
using namespace cocos2d;

map<string,Attribute> PassiveSkill::bonus;

bool PassiveSkill::initExternalData(
	const string &dataPath){

	if(!Skill::initExternalData(dataPath))
		return false;

	auto bonusAttrs =
		json.get("bonus", Json::Value::null);
	if(bonusAttrs == Json::Value::null)
		return false;

	for(auto attr : bonusAttrs){
		string target = attr.get("target", "").asString();
		float value = attr.get("value", 0.0f).asFloat();
		float rate = attr.get("rate", 0.0f).asFloat();

		bonus[target] = Attribute(value, rate);
	}

	return true;
}