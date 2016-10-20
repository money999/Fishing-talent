#pragma once

#include "cocos2d.h"
#include "ScheduleCounterDelegate.h"
USING_NS_CC;

class ScheduleCountDown : public CCNode
{

public:
	ScheduleCountDown();
	~ScheduleCountDown();
	void schedulePerSecond(float delta);

	virtual bool init (ScheduleCounterDelegate* target, int perimeter, bool loop);

	static ScheduleCountDown* ScheduleCountDown::create(ScheduleCounterDelegate* target, int perimeter, bool loop);
protected:
private:
	ScheduleCounterDelegate* _target;
	int _curTime;
	int _maxTime;
	bool _loop;
};