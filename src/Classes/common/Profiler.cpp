#include "pch.h"
#include "Profiler.h"

#include <map>

using namespace std;
using namespace cocos2d;

static struct ProfileData{
	float st;
	float total;
	int depth;

	ProfileData(){
		depth = st = total = 0;
	}
};

static map<string, ProfileData> data;
static int depth = 0;

class Dummy : public Node{
public:
	CREATE_FUNC(Dummy);

	virtual void update(float dt){
		MyProfiler::update(dt);
	}
};

namespace MyProfiler{
	void init(){
		Node *dummy = Dummy::create();
		dummy->retain();
		auto scheduler =
			Director::getInstance()->getScheduler();
		scheduler->scheduleUpdate(
			dummy, -100000000, false);
	}

	void begin(
		const string &name){

		data[name].depth = depth;
		data[name].st = GetTickCount();
		depth ++;
	}
	void end(
		const string &name){

		data[name].depth = depth;
		data[name].total +=
			GetTickCount() - data[name].st;
		depth --;
	}

	void update(float dt){
		printf("PROFILE DATA\n");
		for(auto &pair : data){
			for(int i=0;i<pair.second.depth;i++)
				printf(" ");

			printf("%s : %f\n", 
				pair.first.c_str(),
				pair.second.total);
		}

		data.clear();
	}
};