#include "ScheduleCountDown.h"

ScheduleCountDown::ScheduleCountDown()
{

}

ScheduleCountDown::~ScheduleCountDown()
{

}

ScheduleCountDown* ScheduleCountDown::create( ScheduleCounterDelegate* target, int perimeter, bool loop )
{
	ScheduleCountDown * tt = new ScheduleCountDown();
	tt->autorelease();
	tt->init(target, perimeter, loop);
	return tt;
}

bool ScheduleCountDown::init( ScheduleCounterDelegate* target, int perimeter, bool loop )
{
	_target = target;
	_curTime = perimeter;
	_maxTime = perimeter;
	_loop = loop;

	schedule(schedule_selector(ScheduleCountDown::schedulePerSecond), 1.0f);
	return true;
}

void ScheduleCountDown::schedulePerSecond( float delta )
{
	_curTime--;
	if(_curTime < 0)
	{
		if(_loop)
		{
			_curTime = _maxTime;
			_target->scheduleTimeUp();
		}
		else
		{
			//_target->scheduleTimeUp();
		}
	}
	_target->setScheduleNumber(_curTime);
}
