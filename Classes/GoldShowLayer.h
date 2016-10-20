#pragma once

#include "cocos2d.h"
#include "GoldShow.h"
USING_NS_CC;

class GoldShowLayer : public CCLayer
{
public:
	GoldShowLayer();
	~GoldShowLayer();
	virtual bool init();
	void goldBoxAction();
	void showGold(CCPoint point, int num);
	void callBack(CCObject *sender );
	CREATE_FUNC(GoldShowLayer);
protected:

private:
	CCSprite* goldBox;
	CCPoint goldBoxPosition;
};