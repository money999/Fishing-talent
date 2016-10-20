#include "Fish.h"


Fish::Fish()
{
	_isCaught = false;
}

Fish::~Fish()
{

}

bool Fish::init( FishType type /*= k_Fish_Type_SmallFish*/ )
{
	if(type < 0|| type >= k_Fish_Type_Count-1)
	{
		type = k_Fish_Type_SmallFish;
	}
	_type = type;
	CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation_format"), _type);
	CCAnimation* fishAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
	CCAnimate* fishAnimate = CCAnimate::create(fishAnimation);
	fishAnimate->setTag(k_Action_Animate);

	_fishSprite = CCSprite::create();////////////////////一开始想在这里创建物理世界的框架，发现这个时候精灵还没有宽和高，都是零，测试后发现就算在下面moveTo runaction后，长宽还是零，延迟0.5秒后，长宽有了……
	this->addChild(_fishSprite);
	this->setTag(k_Fish_Tag);//在bezier里用de标签
	//this->addChild(_fishSprite, 0, 999);
	_fishSprite->runAction(CCRepeatForever::create(fishAnimate));

	//CCSprite * sp = (CCSprite *)getChildByTag(999);//在bezier里用标签获取不到，这里却获取得到……

	return true;
}

Fish* Fish::create( FishType type /*= k_Fish_Type_SmallFish*/ )
{
	Fish* fish = new Fish();
	fish->init(type);
	fish->autorelease();
	return fish;
}


void Fish::createPhysicsBody()
{
	//float tt = _fishSprite->getContentSize().width;
	//_fishSprite->setTag(p_fish);
	//PHYSICS_WORLD_ADD_BODY_FOR_SPRITE(_fishSprite);
	CCLog("schedule");
}

//不需要这个函数
void Fish::reset()
{
	stopAllActions();
	//this->setRotation(0);
	_isCaught = false;
	//this->setVisible(true);
}


void Fish::bezierBy( CCPoint startP, CCPoint endP )
{
	int direction = CCRANDOM_0_1()*2;
	if(direction == 0)
		direction = -1;
	CCActionInterval *action = BezierFzj::createBezierFzj(getBezierTime(), startP, endP, -getControlHeigth() * direction, getControlHeigth() * direction);
	CCCallFunc* callfunc = CCCallFunc::create(this,callfunc_selector(Fish::moveEnd));
	CCSequence* seq = CCSequence::create(action,callfunc,NULL);
	seq->setTag(k_Action_MoveTo);
	this->runAction(seq);

	char str[][50] = {"SmallFish","Croaker","AngelFish","Amphiprion","PufferS","Bream","Porgy","Chelonian","Lantern","Ray","Shark","GoldenTrout","GShark","GMarlinsFish","GrouperFish","JadePerch","MarlinsFish","PufferB"};
	CCString *frameSpriteName = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_format"), str[_type],1);
	CCSprite *sprite = CCSprite::createWithSpriteFrameName(frameSpriteName->getCString());

	_fishSprite->setTag(p_fish);
	_fishSprite->setUserData(str[_type]);
	PHYSICS_WORLD_ADD_BODY_FOR_SPRITE_CONTENT(_fishSprite,sprite->getTextureRect().size);
}

void Fish::moveTo(cocos2d::CCPoint destination)
{

	CCPoint start = this->getParent()->convertToWorldSpace(this->getPosition());
	float time = ccpDistance(destination,start)/getSpeed();
	CCMoveTo* moveToo = CCMoveTo::create(time, destination);
	CCCallFunc* callfunc = CCCallFunc::create(this,callfunc_selector(Fish::moveEnd));

	CCFiniteTimeAction* seq = CCSequence::create(moveToo,callfunc,NULL);
	seq->setTag(k_Action_MoveTo);
	this->runAction(seq);

	//this->scheduleOnce(schedule_selector(Fish::createPhysicsBody),1);///这个函数会报错，这错误不会解决故放弃这方法Run-Time Check Failure #0 - The value of ESP was not properly saved across a function call.  This is usually a result of calling a function declared with one calling convention with a function pointer declared with a different calling convention.
	
	char str[][50] = {"SmallFish","Croaker","AngelFish","Amphiprion","PufferS","Bream","Porgy","Chelonian","Lantern","Ray","Shark","GoldenTrout","GShark","GMarlinsFish","GrouperFish","JadePerch","MarlinsFish","PufferB"};
	CCString *frameSpriteName = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_format"), str[_type],1);
	CCSprite *sprite = CCSprite::createWithSpriteFrameName(frameSpriteName->getCString());
	
	_fishSprite->setTag(p_fish);
	_fishSprite->setUserData(str[_type]);
	PHYSICS_WORLD_ADD_BODY_FOR_SPRITE_CONTENT(_fishSprite,sprite->getTextureRect().size);

}

void Fish::moveEnd()
{
	//this->setVisible(false);
	PHYSICS_WORLD_SPRITE_DOWN(_fishSprite);
	stopAllActions();
	this->getParent()->removeChild(this,false);
}

cocos2d::CCRect Fish::getCollisionArea()
{


	//CCPoint fishW = _fishSprite->getParent()->convertToWorldSpace(_fishSprite->getPosition());
	//CCLog("%lf  %lf            %lf  %lf", getPosition().x,getPosition().y,  fishW.x,  fishW.y);

	//CCPoint fishPosition = this->getParent()->convertToWorldSpace(this->getPosition());

	CCPoint fishPosition = _fishSprite->getParent()->convertToWorldSpace(_fishSprite->getPosition());//////////////////////////问题
	CCSize fishSize = _fishSprite->getContentSize();

	//return CCRectMake()可以用这个宏

	CCRect tt;
	tt.setRect(fishPosition.x - fishSize.width/2, fishPosition.y - fishSize.height/2,fishSize.width,fishSize.height);

	//CCLog("eeeeeeeeee     %lf %lf",fishPosition.x,fishPosition.y);
	//CCLog("%lf %lf %lf %lf",tt.origin.x,tt.origin.y,tt.size.width,tt.size.height);

	return tt;
}

void Fish::beCaught()
{
	_isCaught = true;
	stopAllActions();
	//_fishSprite->stopAllActions();
	CCFiniteTimeAction* seq = CCSequence::create(
		CCDelayTime::create(1.0) , 
		CCCallFunc::create(this,callfunc_selector(Fish::beCaught_CallFunc)), 
		NULL);
	runAction(CCSpawn::create(seq, CCBlink::create(1.0, 8), NULL));
}

void Fish::beCaught_CallFunc()
{
	PHYSICS_WORLD_SPRITE_DOWN(_fishSprite);
	this->getParent()->removeChild(this,false);
}

cocos2d::CCSize Fish::fishSize()
{
	char str[][50] = {"SmallFish","Croaker","AngelFish","Amphiprion","PufferS","Bream","Porgy","Chelonian","Lantern","Ray","Shark","GoldenTrout","GShark","GMarlinsFish","GrouperFish","JadePerch","MarlinsFish","PufferB"};
	CCString *frameSpriteName = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_format"), str[_type],1);
	CCSprite *sprite = CCSprite::createWithSpriteFrameName(frameSpriteName->getCString());
	return sprite->getContentSize();
}


float Fish::getBezierTime()
{
	switch(_type)
	{
	case 0:
		return 3.0f;
		break;
	case 1:
		return 3.5f;
		break;
	case 2:
		return 3.0f;
		break;
	case 3:
		return 4.0f;
		break;
	case 4:
		return 5.0f;
		break;
	case 5:
		return 7.0f;
		break;
	case 6:
		return 7.2f;
		break;
	case 7:
		return 7.5f;
		break;
	case 8:
		return 8.3f;
		break;
	case 9:
		return 8.5f;
		break;
	case 10:
		return 9.3f;
		break;
	case 11:
		return 6.0f;
		break;
	case 12:
		return 10.0f;
		break;
	case 13:
		return 9.5f;
		break;
	case 14:
		return 6.2;
		break;
	case 15:
		return 6.5f;
		break;
	case 16:
		return 9.0f;
		break;
	case 17:
		return 65;
		break;
	}
}

int Fish::getFishGold()
{
	switch(_type)
	{
	case 0:
		return 50;
		break;
	case 1:
		return 75;
		break;
	case 2:
		return 100;
		break;
	case 3:
		return 110;
		break;
	case 4:
		return 125;
		break;
	case 5:
		return 180;
		break;
	case 6:
		return 200;
		break;
	case 7:
		return 250;
		break;
	case 8:
		return 300;
		break;
	case 9:
		return 350;
		break;
	case 10:
		return 375;
		break;
	case 11:
		return 145;
		break;
	case 12:
		return 500;
		break;
	case 13:
		return 450;
		break;
	case 14:
		return 150;
		break;
	case 15:
		return 165;
		break;
	case 16:
		return 400;
		break;
	case 17:
		return 65;
		break;

	}

}

float Fish::getFishPro()
{
	switch(_type)
	{
	case 0: 
		return 1.0f;
		break;
	case 1:
		return 0.9f;
		break;
	case 2:
		return 0.88f;
		break;
	case 3:
		return 0.84f;
		break;
	case 4:
		return 0.86f;
		break;
	case 5:
		return 0.8f;
		break;
	case 6:
		return 0.75f;
		break;
	case 7:
		return 0.7f;
		break;
	case 8:
		return 0.55f;
		break;
	case 9:
		return 0.5f;
		break;
	case 10:
		return 0.4f;
		break;
	case 11:
		return 0.65f;
		break;
	case 12:
		return 0.25f;
		break;
	case 13:
		return 0.3f;
		break;
	case 14:
		return 0.68f;
		break;
	case 15:
		return 0.7f;
		break;
	case 16:
		return 0.35f;
		break;
	case 17:
		return 65;
		break;
	}
}

float Fish::getControlHeigth()
{
	switch(_type)
	{
	case 0: 
		return 300.0f;
		break;
	case 1:
		return 285.0f;
		break;
	case 2:
		return 278.0f;
		break;
	case 3:
		return 273.0f;
		break;
	case 4:
		return 265.0f;
		break;
	case 5:
		return 200.0f;
		break;
	case 6:
		return 180.0f;
		break;
	case 7:
		return 150.0f;
		break;
	case 8:
		return 125.0f;
		break;
	case 9:
		return 100.0f;
		break;
	case 10:
		return 150.0f;
		break;
	case 11:
		return 260.0f;
		break;
	case 12:
		return 30.0f;
		break;
	case 13:
		return 50.0f;
		break;
	case 14:
		return 250.0f;
		break;
	case 15:
		return 235.0f;
		break;
	case 16:
		return 75.0f;
		break;
	case 17:
		return 65;
		break;
	}
}

float Fish::getSpeed()
{
	return 300;
}


