#pragma once

#include <string>

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