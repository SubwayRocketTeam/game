#pragma once

#include <string>

///# 실제로는 안쓰는거? 구현이 어디있는겨... 안쓰는거는 주석 또는 삭tothe제하는 습관을..
class DBContext{
public:
	bool connect(
		const std::string &conn);
	void close();
	
	bool execute(
		const std::string &query);

	bool push(
		int value);
	bool push(
		float value);
	bool push(
		const std::string &value);

	int popAsInt();
	float popAsFloat();
	std::string popAsString();

private:
	DBContext();
	virtual ~DBContext();


};