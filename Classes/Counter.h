#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Counter : public CCNode
{
public:

	Counter();
	~Counter();
	void setDigit(int digit);
	void animation(int digit);

	virtual void visit();
	virtual bool init(CCArray* presenters, int digit);
	static Counter* create(CCArray* presenters, int digit);
protected:

private:
	int _digit;
	CCNode* _presenters;
};