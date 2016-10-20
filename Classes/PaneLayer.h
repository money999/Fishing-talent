#pragma once
#include "cocos2d.h"
#include "StaticData.h"
#include "GoldCounterLayer.h"
#include "ScheduleCountDown.h"
#include "ScheduleCounterDelegate.h"
#include "GoldShow.h"
//#include "GameScene.h"//向前定义差点忘了
class GameScene;
USING_NS_CC;
class PaneLayer : public CCLayer, public ScheduleCounterDelegate
{
	CC_SYNTHESIZE_READONLY(GoldCounterLayer*, _goldCounterLayer, GoldCounterLayer);
public:
	PaneLayer();
	~PaneLayer();
	bool init();
	void pause(cocos2d::CCObject *sender);
	void snapshot(cocos2d::CCObject *sender);
	void buttonCall(cocos2d::CCObject *sender);
	void snapshotCall(CCObject *sender);
	void snapshotCall2(CCObject *sender);
	void setMenuResume();
	void goldShowCall(CCObject *sender);

	void scheduleTimeUp();
	void setScheduleNumber(int number);

	CREATE_FUNC(PaneLayer);
protected:
private:
	CCLabelTTF *_scheduleLabel;
	CCMenu *leftMenu, *rightMenu;
};