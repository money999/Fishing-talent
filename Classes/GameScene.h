#pragma once
#include "cocos2d.h"
#include "PaneLayer.h"
#include "BackgroundLayer.h"
#include "Fish.h"
#include "FishLayer.h"
#include "cocos-ext.h" 
#include "CannonLayer.h"
#include "MenuLayer.h"
#include "TouchLayer.h"
#include "FishingJoyData.h"
#include "PersonalAudioEngine.h"
#include "GoldShowLayer.h"

#include "PhysicsWorldFzj.h"

#define MENU_LAYER_TAG 999

typedef enum{
	k_Operate_Pause = 0,
	k_Operate_Resume
}OperateFlag;

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class GameScene : public CCScene
{
	CC_SYNTHESIZE(OperateFlag, _nowRunStatus, RunStatus);
public:
	GameScene();
	~GameScene();
	
	void preloadResources();
	void pauseAndContinue();
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	void cannonAimAt(CCPoint target);
	void cannonShootTo(CCPoint target);
	bool checkOutCollisionBetweenFishesAndBullet(Bullet *bullet);
	void checkOutCollision();
	void fishWillBeCaught(Fish* fish, Bullet* bullet);
	void checkOutCollisionBetweenFishesAndFishingNet(Bullet *bullet);
	void alterGold(int delta);
	void scheduleTimeUp();
	void showCountDown(int i);
	void showCountDownCallback(CCObject *sender);
	void goldBoxAction();
	
	virtual void onEnterTransitionDidFinish();
	virtual bool init(int type);
	virtual void update(float delta);
	//virtual void draw();

	static GameScene* create(int type);
	//CREATE_FUNC(GameScene);
protected:
	
	PaneLayer *_paneLayer;
	BackgroundLayer *_backgroudLayer;
	FishLayer *_fishLayer;
	CannonLayer *_cannonLayer;
	MenuLayer *_menuLayer;
	TouchLayer *_touchLayer;
	GoldShowLayer *_goldShowLayer;

	GLESDebugDraw *mTestDraw;

private:
	int _type;
};
