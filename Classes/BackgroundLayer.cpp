#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer()
{
	;
}

BackgroundLayer::~BackgroundLayer()
{
	;
}


bool BackgroundLayer::init(const char* strBackground)
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		//const char* strBackgroundPNG = STATIC_DATA_STRING("game_background_01");
		const char* strBackgroundPNG = strBackground;
		CC_BREAK_IF(!strBackgroundPNG);
		CCTexture2D* texture2d = CCTextureCache::sharedTextureCache()->addImage(strBackgroundPNG);
		CC_BREAK_IF(!texture2d);
		CCSprite *bkSprite = CCSprite::createWithTexture(texture2d);
		CC_BREAK_IF(!bkSprite);
		bkSprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));//CCPointMake(бн,бн);
		this->addChild(bkSprite);

		/*Cannon* tt = Cannon::create();
		tt->setPosition(ccp(300,300));
		addChild(tt);*/
		return true;
	} while (0);
	return false;
}

BackgroundLayer * BackgroundLayer::create( const char* strBackground )
{
	BackgroundLayer *tt = new BackgroundLayer();
	tt->init(strBackground);
	tt->autorelease();
	return tt;
}


