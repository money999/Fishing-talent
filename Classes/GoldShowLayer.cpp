#include "GoldShowLayer.h"

GoldShowLayer::GoldShowLayer()
{

}

GoldShowLayer::~GoldShowLayer()
{

}

bool GoldShowLayer::init()
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
		goldBox = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("gold_box")));
		goldBox->setPosition(ccp(winSize.width * 0.2, winSize.height * 0.04));
		addChild(goldBox);
		goldBoxPosition = goldBox->getPosition();
		return true;
	} while (0);
	return false;
}

void GoldShowLayer::showGold( CCPoint point, int num )
{
	GoldShow *tmp = GoldShow::create(num);
	tmp->setPosition(point);
	addChild(tmp);
	tmp->setScale(0.0f);
	CCSpawn *spawn = CCSpawn::create(CCMoveTo::create(1.0f,goldBoxPosition),CCScaleTo::create(1.0f,0.1f),NULL);
	float scaleTo = 1.0f;
	if(num > 300)/////////////////大于300分数夸张显示
		scaleTo = 2.0f;
	CCSequence *seq = CCSequence::create(CCScaleTo::create(0.5f, scaleTo), CCBlink::create(0.5f, 3),spawn, CCCallFuncO::create(this, callfuncO_selector(GoldShowLayer::callBack),(CCObject *)tmp), NULL);
	tmp->runAction(seq);
}

void GoldShowLayer::callBack( CCObject *sender )
{
	GoldShow *tmp = (GoldShow *)sender;
	removeChild(tmp);
	goldBox->stopAllActions();
	goldBox->setPosition(goldBoxPosition);
	goldBox->runAction(CCJumpTo::create(1.5f, goldBoxPosition, 30, 3));
}

void GoldShowLayer::goldBoxAction()
{
	goldBox->stopAllActions();
	goldBox->setPosition(goldBoxPosition);
	goldBox->runAction(CCJumpTo::create(1.5f, goldBoxPosition, 30, 3));
}



