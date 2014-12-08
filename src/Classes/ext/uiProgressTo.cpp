#include "pch.h"
#include "uiProgressTo.h"

#include "ui/UILoadingBar.h"

namespace cocos2d{

UiProgressTo* UiProgressTo::create(float duration, float percent)
{
	auto p = new UiProgressTo();
    p->initWithDuration(duration, percent);
    p->autorelease();

    return p;
}

bool UiProgressTo::initWithDuration(float duration, float percent)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = percent;

        return true;
    }

    return false;
}

UiProgressTo* UiProgressTo::clone() const
{
	// no copy constructor	
	auto a = new (std::nothrow) UiProgressTo();
    a->initWithDuration(_duration, _to);
	a->autorelease();
	return a;
}

UiProgressTo* UiProgressTo::reverse() const
{
	CCASSERT(false, "reverse() not supported in UiProgressTo");
	return nullptr;
}

void UiProgressTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
	_from = ((ui::LoadingBar*)(target))->getPercent();
}

void UiProgressTo::update(float time)
{
    ((ui::LoadingBar*)(_target))->setPercent(_from + (_to - _from) * time);
}

};