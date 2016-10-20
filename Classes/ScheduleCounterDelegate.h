#pragma once

class ScheduleCounterDelegate
{
public:
	ScheduleCounterDelegate(){};
	~ScheduleCounterDelegate(){};
	//virtual ~ScheduleCounterDelegate() = 0;
	virtual void scheduleTimeUp() = 0;
	virtual void setScheduleNumber(int number){};
};