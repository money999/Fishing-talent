#include "GameMenuScene.h"

GameMenuScene::GameMenuScene()
{

}

GameMenuScene::~GameMenuScene()
{

}

bool GameMenuScene::init()
{
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		_menuLayer = GameMenuLayer::create();
		addChild(_menuLayer);
		return true;
	} while (0);
	return false;
}

void GameMenuScene::buttonCallBack( CCObject* pSender )
{
	
}

void GameMenuScene::addPopup()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	PopupLayer* popup = PopupLayer::create("popupback.png");
	popup->setPosition(ccp(winSize.width *0.5, winSize.height*0.5));
	popup->setCallBackFunc(this, callfuncN_selector(GameMenuScene::buttonCallBack));
	this->addChild(popup);
}

