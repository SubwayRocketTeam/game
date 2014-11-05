#pragma once

#include "cocos2d.h"

// Hp �Ǵ� Mp
class Gauge : public cocos2d::Sprite {
public:
	Gauge();
	~Gauge();

	bool initWithFile(const std::string &name);
	void update(float dt) override;

	static Gauge* create(const std::string &name, float _targetWidth, int _max = 0);
	
	/**
	 * ����ü�°� �ִ�ü���� ������ ��ȯ��
	 */
	float getNowToMaxRatio() {
		return now / max;
	}

	/**
	 * �ʴ� ȸ���Ǵ� ���� ����
	 */
	void setRegenPerSec(float _regenPerSec) {
		if (_regenPerSec >= 0) {
			regenPerSec = _regenPerSec;
		}
	}

	/**
	 * ���� ü���� _value��ŭ ���ҽ�Ŵ
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