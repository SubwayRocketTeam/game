#include "pch.h"
#include "PassiveSkill.h"

using namespace std;
using namespace cocos2d;

bool PassiveSkill::initExternalData(
	const string &dataPath){

	if(!Skill::initExternalData(dataPath))
		return false;

	interval =
		json.get("interval", 0).asFloat();

	auto bonusAttrs =
		json.get("bonus", Json::Value::null);
	if(bonusAttrs == Json::Value::null)
		return false;

	for(auto attr : bonusAttrs){
		string target = attr.get("target", "").asString();
		float value = attr.get("value", 0.0f).asFloat();
		float rate = attr.get("rate", 0.0f).asFloat();

		bonusList[target] = Attribute(value, rate);
	}

	return true;
}

bool PassiveSkill::update(
	Unit *user, float remaining){

	/* false ���Ͻ� ���� �нú� ���� */
	return true;
}