#pragma once

class ProgressDelegate
{
public:
	ProgressDelegate(){};
	~ProgressDelegate(){};
	virtual void loadingFinished() = 0;
	virtual void progressPercentageSetter(float percentage){};
protected:
private:
};