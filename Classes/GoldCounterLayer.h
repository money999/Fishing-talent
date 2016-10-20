#pragma once

#include "cocos2d.h"
#include "Counter.h"
USING_NS_CC;

class GoldCounterLayer : public CCLayer
{
public:
	GoldCounterLayer();
	~GoldCounterLayer();
	static GoldCounterLayer* create(int number = 1314520);
	virtual bool init(int number);

	void setNumber(int number, int ceiling = 9999999);
protected:

private:
	int _number;
};