#pragma once

#include "cocos2d.h"

namespace cocos2d{

class UiProgressTo : public ActionInterval{
public:
    static UiProgressTo* create(float duration, float percent);

    //
    // Overrides
    //
	virtual UiProgressTo* clone() const override;
	virtual UiProgressTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    UiProgressTo() {}
	virtual ~UiProgressTo() {}

    bool initWithDuration(float duration, float percent);

protected:
    float _to;
    float _from;
};

};