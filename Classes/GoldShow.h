#pragma once

#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class GoldShow : public CCNode
{
public:
	GoldShow();
	~GoldShow();
	virtual bool init(int num);
	
	static GoldShow* create(int num);
protected:

private:
	CCArray *num;
};