#pragma once
#include "cocos2d.h"
#include "StaticData.h"
#include "SpriteButtonFzj.h"
#include "cocos-ext.h" 
#include "WhereScene.h"
#include "LoadingLayer.h"
USING_NS_CC;
//USING_NS_CC_EXT;
class GameMenuScene;
using namespace cocos2d::extension;

using namespace std;

class GameMenuLayer : public CCLayer
{
	
public:
	GameMenuLayer();
	~GameMenuLayer();
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	static CCScene * scene();
	CREATE_FUNC(GameMenuLayer);

protected:
	void createMenu();
	void menuCallbackStartGame(CCObject *sender);
	void menuCallbackSelectScene(CCObject *sender);
	void menuCallbackButtonMy(CCObject *sender);

};