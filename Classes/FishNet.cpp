#include "FishNet.h"

FishNet::FishNet()
{

}

FishNet::~FishNet()
{

}

bool FishNet::init()
{
	CCString* fileName = CCString::createWithFormat(STATIC_DATA_STRING("net_frame_format"),1);
	_fishNetSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
	//_fishNetSprite->setAnchorPoint(ccp(0.5,1.0));
	addChild(_fishNetSprite);
	return true;
}

float FishNet::getFireRange()
{
	return 1.0f;
}


void FishNet::end()
{
	PHYSICS_WORLD_SPRITE_DOWN(_fishNetSprite);
}


void FishNet::showAt( CCPoint pos,int type /*= 0*/ )
{
	
	CCString *frameSpriteName = CCString::createWithFormat(STATIC_DATA_STRING("net_frame_format"),type + 1);
	CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameSpriteName->getCString());
	_fishNetSprite->setDisplayFrame(spriteFrame);

	setPosition(pos);
	setVisible(true);

	CCParticleSystemQuad *particleSystemQuad = (CCParticleSystemQuad *)this->getUserObject();
	particleSystemQuad->setPosition(pos);
	particleSystemQuad->resetSystem();
	CCCallFunc* callfunc = CCCallFunc::create(this,callfunc_selector(FishNet::end));
	stopAllActions();
	CCSequence *seq1 = CCSequence::create(CCDelayTime::create(1.0),CCHide::create(),NULL);
	CCSequence *seq2 = CCSequence::create(CCDelayTime::create(CCDirector::sharedDirector()->getAnimationInterval()),callfunc,NULL);//下一帧让body消失就不会碰撞了
	runAction(CCSpawn::create(seq1, seq2, NULL));

	PersonalAudioEngine::sharedEngine()->playEffect(kEffectFishNet);
	_fishNetSprite->setTag(p_fishnet);
	PHYSICS_WORLD_ADD_BODY_FOR_SPRITE(_fishNetSprite);
}

cocos2d::CCRect FishNet::getCollisionArea()
{
	CCPoint fishNetWorldPos = this->getParent()->convertToWorldSpace(this->getPosition());
	CCSize fishNetSize = _fishNetSprite->getContentSize();
	
	CCRect tt;
	tt.setRect(fishNetWorldPos.x - fishNetSize.width/2, fishNetWorldPos.y - fishNetSize.height/2, fishNetSize.width, fishNetSize.height);
	return tt;
}

CCSprite* FishNet::getFishNetSprite()
{
	return _fishNetSprite;
}

