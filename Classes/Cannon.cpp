#include "Cannon.h"

Cannon::Cannon()
{

}

Cannon::~Cannon()
{
	CC_SAFE_RELEASE(_cannonSprites);
}


bool Cannon::init(CannonType type /*= k_Cannon_Type_1*/)
{
	if(!CCNode::init())
	{
		return false;
	}
	_cannonSprites = CCArray::createWithCapacity(k_Cannon_Count);
	for(int i = k_Cannon_Type_1;i<k_Cannon_Count; i++)
	{
		const char *fileName = CCString::createWithFormat(STATIC_DATA_STRING("cannon_frame_format"),i + 1)->getCString();
		CCSprite *cannonSprite = CCSprite::createWithSpriteFrameName(fileName);
		_cannonSprites->addObject(cannonSprite);
		//cannonSprite->ignoreAnchorPointForPosition(false);  
		cannonSprite->setAnchorPoint(ccp(0.5,0.25));
	}
	//_cannonSprites->retain();
	CC_SAFE_RETAIN(_cannonSprites);
	setType(type);
	return true;
}

void Cannon::setType(CannonType var)
{
	if(_type == var)
	{
		return ;
	}
	if(var < k_Cannon_Type_1)
	{
		var = (CannonType)(k_Cannon_Count - 1);
	}
	else if(var >= k_Cannon_Count)
	{
		var = (CannonType)k_Cannon_Type_1;
	}
	if(getChildrenCount() != 0)//虽然这句可以不加，在跟踪调试后发现时没有关系的，内部会自动判别，并有Log提示：cocos2d: removeChildByTag(tag = -842150451): child not found!
	{
		CCSprite *cannonSp = (CCSprite*)_cannonSprites->objectAtIndex(_type);
		cannonSp->runAction(CCSequence::create(CCScaleTo::create(0.2f,0.1f),CCCallFunc::create(this,callfunc_selector(Cannon::call_fun_cannon1)),NULL));
		_now = var;
	}
	else
	{
		CCSprite *cannonSprite = (CCSprite*)_cannonSprites->objectAtIndex(var);
		addChild(cannonSprite,0,var);
		_type = var;
	}

	
}

CannonType Cannon::getType()
{
	return _type;
}

Cannon * Cannon::create( CannonType type /*= k_Cannon_Type_1*/ )
{
	Cannon *tt = new Cannon();
	tt->init(type);
	tt->autorelease();
	return tt;
}

void Cannon::aimAt( CCPoint target )
{
	CCPoint cannonPoint = getParent()->convertToWorldSpace(this->getPosition());
	float angle = ccpAngleSigned(ccpSub(target,cannonPoint),ccp(0,1));
	//this->setRotation(CC_RADIANS_TO_DEGREES(angle));
	//CCLog("%lf",angle);
	if(angle>=-1.55 && angle <= 1.55)
		this->setRotation(CC_RADIANS_TO_DEGREES(angle));
}

void Cannon::call_fun_cannon1()
{
	removeChildByTag(_type);
	//CannonType nowData = *((CannonType *)pData);//还想用callfuncND传参数的，额可惜失败了
	CCSprite *cannonSp = (CCSprite*)_cannonSprites->objectAtIndex(_now);
	cannonSp->setScale(0.0f);
	addChild(cannonSp,0,_now);
	cannonSp->runAction(CCSequence::create(CCScaleTo::create(0.2f,1.0f)/*,CCCallFunc::create(this,callfunc_selector(Cannon::call_fun_cannon2))*/,NULL));
	_type = _now;
}

void Cannon::call_fun_cannon2()
{
	CCLog("rrrrrrrrrrrrrr");
}

int Cannon::getCannonCost()
{
	switch(_type)
	{
	case 0: 
		return 100;
		break;
	case 1:
		return 200;
		break;
	case 2:
		return 250;
		break;
	case 3:
		return 300;
		break;
	case 4:
		return 350;
		break;
	case 5:
		return 400;
		break;
	case 6:
		return 500;
		break;
	}
}