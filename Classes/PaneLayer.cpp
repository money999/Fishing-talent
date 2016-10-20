#include "PaneLayer.h"
#include "GameScene.h"

PaneLayer::PaneLayer()
{

}

PaneLayer::~PaneLayer()
{

}

bool PaneLayer::init()
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();


		CCSprite* pauseNormalSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("button_pause_normal"));
		CCSprite* pauseSelectedSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("button_pause_selected"));
		CCSprite* musicNormalSprite = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("button_music_normal")));
		CCSprite* musicSelectedSprite = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("button_music_selected")));
		CCSprite* snapNormalSprite = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("button_photo_normal")));
		CCSprite* snapSelectedSprite = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("button_photo_selected")));
		CCSprite* fishNormalSprite = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("button_fish_normal")));
		CCSprite* fishSelectedSprite = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("button_fish_selected")));
		pauseNormalSprite->setScale(0.6f);//////////////android的暂停图片缺角，就全用ipad版的，所以这里集体缩小
		pauseSelectedSprite->setScale(0.6f);
		musicNormalSprite->setScale(0.6f);
		musicSelectedSprite->setScale(0.6f);
		snapNormalSprite->setScale(0.6f);
		snapSelectedSprite->setScale(0.6f);
		fishNormalSprite->setScale(0.6f);
		fishSelectedSprite->setScale(0.6f);
		

		CCMenuItemSprite* pauseItem = CCMenuItemSprite::create(pauseNormalSprite,pauseSelectedSprite,this,menu_selector(PaneLayer::pause));
		CCMenuItemSprite* musicItem = CCMenuItemSprite::create(musicNormalSprite,musicSelectedSprite,this,menu_selector(PaneLayer::pause));
		CCMenuItemSprite* snapItem = CCMenuItemSprite::create(snapNormalSprite,snapSelectedSprite,this,menu_selector(PaneLayer::snapshot));
		CCMenuItemSprite* fishItem = CCMenuItemSprite::create(fishNormalSprite,fishSelectedSprite,this,menu_selector(PaneLayer::pause));

		leftMenu = CCMenu::create(pauseItem, musicItem,NULL);
		leftMenu->alignItemsHorizontallyWithPadding(50);
		leftMenu->setPosition(ccp(winSize.width * 0.15, winSize.height * 0.98));

		rightMenu = CCMenu::create(snapItem, fishItem,NULL);
		rightMenu->alignItemsHorizontallyWithPadding(50);
		rightMenu->setPosition(ccp(winSize.width * 0.88, winSize.height * 0.98));

		addChild(leftMenu);
		addChild(rightMenu);

		_goldCounterLayer = GoldCounterLayer::create(1314520);
		_goldCounterLayer->setPosition(327.0f,32.0f);
		addChild(_goldCounterLayer);
		
		int fontSize=40;
		CCString *fontName = CCString::create("Thonburi");//字体的名称,没有用默认的
		_scheduleLabel = CCLabelTTF::create(STATIC_DATA_STRING("count_down"), fontName->getCString(), fontSize);
		_scheduleLabel->setColor(ccBLUE);
		ScheduleCountDown* countDown = ScheduleCountDown::create(this,STATIC_DATA_INT("count_down") , true);
		_scheduleLabel->addChild(countDown);
		_scheduleLabel->setPosition(ccp(640,770));
		addChild(_scheduleLabel);

		CCString *tt;
		tt = CCString::createWithFormat(STATIC_DATA_STRING("button_prop_format"),1);
		CCSprite* buttonSp1 = CCSprite::createWithTexture(textureCache->textureForKey(tt->getCString()));
		CCMenuItemSprite* buutonItem1 = CCMenuItemSprite::create(buttonSp1, buttonSp1, this,menu_selector(PaneLayer::buttonCall) );

		tt = CCString::createWithFormat(STATIC_DATA_STRING("button_prop_format"),2);
		CCSprite* buttonSp2 = CCSprite::createWithTexture(textureCache->textureForKey(tt->getCString()));
		CCMenuItemSprite* buutonItem2 = CCMenuItemSprite::create(buttonSp2, buttonSp2, this,menu_selector(PaneLayer::buttonCall) );

		tt = CCString::createWithFormat(STATIC_DATA_STRING("button_prop_format"),3);
		CCSprite* buttonSp3 = CCSprite::createWithTexture(textureCache->textureForKey(tt->getCString()));
		CCMenuItemSprite* buutonItem3 = CCMenuItemSprite::create(buttonSp3, buttonSp3, this,menu_selector(PaneLayer::buttonCall) );

		tt = CCString::createWithFormat(STATIC_DATA_STRING("button_prop_format"),4);
		CCSprite* buttonSp4 = CCSprite::createWithTexture(textureCache->textureForKey(tt->getCString()));
		CCMenuItemSprite* buutonItem4 = CCMenuItemSprite::create(buttonSp4, buttonSp4, this,menu_selector(PaneLayer::buttonCall) );
		
		CCMenu *menuImage = CCMenu::create(buutonItem1, buutonItem2, buutonItem3, buutonItem4, NULL);
		menuImage->alignItemsHorizontallyWithPadding(4);
		menuImage->setPosition(ccp(winSize.width * 0.705, winSize.height * 0.04));
		addChild(menuImage);

		return true;
	} while (0);
	return false;
}

void PaneLayer::pause( cocos2d::CCObject *sender )
{
	leftMenu->setTouchEnabled(false);
	rightMenu->setTouchEnabled(false);
	((GameScene*)this->getParent())->pauseAndContinue();
}

void PaneLayer::scheduleTimeUp()
{
	//_scheduleLabel->setVisible(false);
	GameScene* gameScene = (GameScene *)getParent();
	gameScene-> scheduleTimeUp();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	GoldShow *tmp = GoldShow::create(STATIC_DATA_INT("recovery_gold"));
	tmp->setPosition(_scheduleLabel->getPosition());
	addChild(tmp);
	tmp->setScale(0.0f);
	CCSpawn *spawn = CCSpawn::create(CCMoveTo::create(1.0f,ccp(winSize.width * 0.2, winSize.height * 0.04)),CCScaleTo::create(1.0f,0.1f),NULL);
	float scaleTo = 1.0f;
	CCSequence *seq = CCSequence::create(CCScaleTo::create(0.5f, scaleTo),spawn, CCCallFuncO::create(this, callfuncO_selector(PaneLayer::goldShowCall),(CCObject *)tmp), NULL);
	tmp->runAction(seq);

}

void PaneLayer::setScheduleNumber( int number )
{
	CCString *tt = CCString::createWithFormat("%d",number);
	_scheduleLabel->setString(tt->getCString());
}

void PaneLayer::setMenuResume()
{
	leftMenu->setTouchEnabled(true);
	rightMenu->setTouchEnabled(true);
}

void PaneLayer::buttonCall( cocos2d::CCObject *sender )
{

}

void PaneLayer::snapshot( cocos2d::CCObject *sender )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCRenderTexture *texture = CCRenderTexture::create(winSize.width,winSize.height);
	texture->setPosition(winSize.width * 0.5, winSize.height * 0.5);
	texture->begin();
	CCDirector::sharedDirector()->getRunningScene()->visit();
	texture->end();
	if(texture->saveToFile("screenshot.png",kCCImageFormatPNG))
	{

		CCLayerColor *lc = CCLayerColor::create(ccc4(255, 255, 255, 255));
		lc->setAnchorPoint(CCPointZero);
		addChild(lc);
		lc->runAction(CCSequence::create(CCFadeOut::create(1.0),CCCallFuncO::create(this,callfuncO_selector(PaneLayer::snapshotCall2),(CCObject*)lc),NULL));
		PersonalAudioEngine::sharedEngine()->playEffect(kEffectSnapshot);

		int fontSize=22;
		CCString *fontName = CCString::create("Thonburi");
		CCLabelTTF *ttf = CCLabelTTF::create("snapshot success",fontName->getCString(),fontSize);
		CCPoint cp = rightMenu->getPosition();
		cp.x -= 100;
		cp.y -= 70;
		ttf->setPosition(cp);
		CCSpawn *spawn1 = CCSpawn::create(CCMoveTo::create(1.0f, ccp(cp.x, cp.y - 30)), CCFadeIn::create(1.0f), NULL);
		CCSpawn *spawn2 = CCSpawn::create(CCMoveTo::create(1.0f, ccp(cp.x, cp.y + 30)), CCFadeOut::create(1.0f), NULL);
		ttf->runAction(CCSequence::create(spawn1,CCDelayTime::create(2.0f),spawn2,CCCallFuncO::create(this, callfuncO_selector(PaneLayer::snapshotCall), (CCObject*)ttf),NULL));
		addChild(ttf);
	}
}

void PaneLayer::snapshotCall(CCObject *sender)
{
	CCLabelTTF *ttf = (CCLabelTTF *)sender;
	removeChild(ttf);
}

void PaneLayer::snapshotCall2( CCObject *sender )
{
	CCSprite *spSnap = (CCSprite *)sender;
	removeChild(spSnap);
}

void PaneLayer::goldShowCall( CCObject *sender )
{
	GoldShow *tmp = (GoldShow *)sender;
	removeChild(tmp);

	((GameScene *)this->getParent())->goldBoxAction();
}
