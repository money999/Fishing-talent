#include "Weapon.h"


Weapon::Weapon()
{
	
}

Weapon::~Weapon()
{
	CC_SAFE_RELEASE(_bullets);
	CC_SAFE_RELEASE(_fishNets);
}

CCSize Weapon::getCannonSize()
{
	CCSprite * sprite = (CCSprite *)_cannon->getCannonSprites()->objectAtIndex(_cannon->getType());
	return sprite->getContentSize();
}



bool Weapon::init( CannonType type /*= k_Cannon_Type_1*/ )
{
	
	_bullets = CCArray::createWithCapacity(BULLET_COUNTS);
	_fishNets  =CCArray::createWithCapacity(BULLET_COUNTS);
	_particles = CCArray::createWithCapacity(BULLET_COUNTS);
	CC_SAFE_RETAIN(_bullets);
	CC_SAFE_RETAIN(_fishNets);

	for(int i =0 ;i<BULLET_COUNTS;i++ )
	{
		Bullet *bullet = Bullet::create();
		_bullets->addObject(bullet);
		addChild(bullet);
		bullet->setVisible(false);


		FishNet *fishNet = FishNet::create();
		_fishNets->addObject(fishNet);
		addChild(fishNet);
		fishNet->setVisible(false);

		bullet->setUserObject(fishNet);//用来加CC相关的
		//bullet->setUserData();// 用来加C++相关的

		const char *stringTemp = STATIC_DATA_STRING("net_particle");
		CCParticleSystemQuad *particleSystemQuad = CCParticleSystemQuad::create(stringTemp);
		_particles->addObject(particleSystemQuad);
		addChild(particleSystemQuad);
		particleSystemQuad->stopSystem();

		fishNet->setUserObject(particleSystemQuad);

	}

	_cannon = Cannon::create(type);
	addChild(_cannon);

	return true;
}

Weapon* Weapon::create( CannonType type /*= k_Cannon_Type_1*/ )
{
	Weapon *tt = new Weapon();
	tt->init(type);
	tt->autorelease();
	return tt;
}

void Weapon::changeCannon( CannonOperate operate )
{
	CannonType t = _cannon->getType();
	if(operate == k_Cannon_Operate_Up)
	{
		_cannon->setType((CannonType)(_cannon->getType() + 1));
	}
	else if(operate == k_Cannon_Operate_Down)
	{
		_cannon->setType((CannonType)(_cannon->getType() - 1));
	}
}

void Weapon::aimAt( CCPoint target )
{
	_cannon->aimAt(target);
}

void Weapon::shootTo( CCPoint target )
{
	Bullet* bullet = getBulletToShoot();
	if(bullet == NULL)
		return ;
	float distance = 90 * (_cannon->getType()+1) + 300;

	CCPoint	weaponWordSpace = this->getParent()->convertToWorldSpace(this->getPosition());
	float touchWeaponDis = ccpDistance(weaponWordSpace,target);

	if(touchWeaponDis > distance)
	{
		CCPoint normal = ccpNormalize(ccpSub(target,weaponWordSpace));
		CCPoint mult = ccpMult(normal,distance);
		target = ccpAdd(getPosition(),mult);
	}

	bullet->flyTo(target,_cannon->getType(),getCannonSize());
}

Bullet* Weapon::getBulletToShoot()
{
	int countHas = 0;
	CCObject* iterator;
	CCARRAY_FOREACH(_bullets, iterator)
	{
		Bullet* bullet = (Bullet*)iterator;
		if(bullet->isVisible() == false)
			return bullet;
		countHas++;
		if(BULLET_COUNTS == countHas)
			break;
	}
	return NULL;
}

CCArray* Weapon::getBullets()
{
	return _bullets;
}

void Weapon::end( Bullet *bullet )
{
	CCPoint bulletPosition = bullet->getPosition();
	bullet->end();
	FishNet *fishnet = (FishNet *)bullet->getUserObject();
	fishnet->showAt(bulletPosition);
}

cocos2d::CCRect Weapon::getCollisionArea( Bullet *bullet )
{
	FishNet *fishNet = (FishNet *)bullet->getUserObject();
	if(fishNet->isVisible())
	{
		return fishNet->getCollisionArea();
	}
	else
	{
		return CCRectZero;
	}
}
