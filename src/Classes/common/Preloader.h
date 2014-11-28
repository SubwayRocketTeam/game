#pragma once

#include "cocos2d.h"

#include <string>
#include <stack>
#include <map>

class Preloader : cocos2d::Ref{
private:
	struct Transaction;
	struct ResourceData;

	enum ResourceType{
		BGM,
		SoundEffect,
		Plist
	};

public:
	static Preloader *create();
	static Preloader *getInstance();
	
	bool push(
		const std::string &name);
	void pop(
		const std::string &name);

protected:
	Preloader();
	virtual ~Preloader();

	virtual void loadBGM(
		const std::string &name);
	virtual void loadSoundEffect(
		const std::string &name);
	virtual void loadPlist(
		const std::string &name);
	virtual void unloadBGM(
		const std::string &name);
	virtual void unloadSoundEffect(
		const std::string &name);
	virtual void unloadPlist(
		const std::string &name);

	void load(
		ResourceType type,
		const std::string &name);
	void unload(
		ResourceType type,
		const std::string &name);

private:
	std::map<std::string,ResourceData> resources;
};