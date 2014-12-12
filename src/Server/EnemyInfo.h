#pragma once

class Attribute;
class ActiveSkill;

struct EnemyInfo {
	std::string name;
	std::map<std::string, Attribute> attrs;
	std::vector<ActiveSkill*> skills;
	int pay;
};