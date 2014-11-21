#pragma once

#include <string>

#define _BEGIN(name) \
	MyProfiler::begin(#name);
#define _END(name) \
	MyProfiler::end(#name);

namespace MyProfiler{
	void init();

	void begin(
		const std::string &name);
	void end(
		const std::string &name);

	void update(float dt);
};