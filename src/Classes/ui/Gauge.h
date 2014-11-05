#pragma once

#include "cocos2d.h"

// Hp 또는 Mp
class Gauge : public cocos2d::Sprite {
public:
	Gauge();
	~Gauge();

	bool initWithFile(const std::string &name);
	void update(float dt) override;

	static Gauge* create(const std::string &name, float _targetWidth, int _max = 0);
	
	/**
	 * 현재체력과 최대체력의 비율을 반환함
	 */
	float getNowToMaxRatio() {
		return now / max;
	}

	/**
	 * 초당 회복되는 양을 정함
	 */
	void setRegenPerSec(float _regenPerSec) {
		if (_regenPerSec >= 0) {
			regenPerSec = _regenPerSec;
		}
	}

	/**
	 * 현재 체력을 _value만큼 감소시킴
	 */
	void reduceGauge(float _value) {
		if (now - _value > 0) {
			now -= _value;
		}
	}

private:
	float max;
	float now;

	float regenPerSec;
	float targetWidth;
};