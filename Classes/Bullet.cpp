#include "Bullet.h"

enum{
	k_Bullet_Action = 0
};


Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

bool Bullet::init()
{
	CCString* fileName = CCString::createWithFormat(STATIC_DATA_STRING("bullet_frame_format"),1);
	_bulletSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
	//_bulletSprite->setAnchorPoint(ccp(0.5,0.9));//����1.0ͷ����һ��հף�ͨ��debugDraw���ָı�ê������������body���λ�����ɻᷢ���ı�
	addChild(_bulletSprite);
	return true;
}

void Bullet::end()
{
	FishNet *fishNet = (FishNet *)this->getUserObject();
	fishNet->showAt(getPosition(),_typeBullet);

	stopActionByTag(k_Bullet_Action);

	PHYSICS_WORLD_SPRITE_DOWN(_bulletSprite);
	setVisible(false);
	
}

void Bullet::flyTo( CCPoint targetInWordSpace, int type/*=0*/ , CCSize cannonSize)
{

	_typeBullet = type;

	CCPoint startInNodeSpace = CCPointZero;
	CCPoint	startInWordSpace = this->getParent()->convertToWorldSpace(startInNodeSpace);
	CCPoint targetInNodeSpace = this->getParent()->convertToNodeSpace(targetInWordSpace);
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	float angle = ccpAngleSigned(ccpSub(targetInWordSpace,startInWordSpace),ccp(0,1));
	float angleDegree = CC_RADIANS_TO_DEGREES(angle);

	//this->setRotation(angleDegree);
	_bulletSprite->setRotation(angleDegree);//��Ϊ��physics�ڲ��õ��Ǿ���ĽǶȣ���������Ľڵ�ǶȲ��ã�Ҫ����ģ�Ҫ��Ȼ���������body�Ƕ�û���ı��ˣ���Ϊbody���澫��ĽǶȵģ�
	//CCLOG("%lf",CC_RADIANS_TO_DEGREES(angle));

	float yStart = (cannonSize.height - _bulletSprite->getContentSize().height) * cos(fabs(angle));//////////�ٸ�Ϊʲô��������ԣ���x��y�Ƿ��ġ���
	float xStart = (cannonSize.height - _bulletSprite->getContentSize().height) * sin(fabs(angle));

	if(angleDegree < 0)
		xStart = -xStart;
	
	//CCLOG("%lf %lf %lf %lf  %lf  %lf  %lf",cos(fabs(angle)), sin(fabs(angle)), angle, angleDegree,  cannonSize.height, xStart, yStart);

	setPosition(ccp(xStart,yStart));//ʹ�ӵ�����̨�ڴ��
	//setPosition(CCPointZero);

	CCString *frameSpriteName = CCString::createWithFormat(STATIC_DATA_STRING("bullet_frame_format"),type + 1);
	CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameSpriteName->getCString());
	//CCLOG(frameSpriteName->getCString());
	_bulletSprite->setDisplayFrame(spriteFrame);//����ͼƬԭ����������ģ������log��ʾ��ͼƬ��û�����ǸĲ����������ڿ��Ѿ�����ԭ����

	setVisible(true);

	float time = ccpDistance(targetInWordSpace,startInWordSpace)/getBulletSpeed();
	CCMoveTo* moveTo = CCMoveTo::create(time, targetInNodeSpace);
	CCCallFunc* callfunc = CCCallFunc::create(this,callfunc_selector(Bullet::end));

	CCFiniteTimeAction* seq = CCSequence::create(moveTo,callfunc,NULL);
	seq->setTag(k_Bullet_Action);
	this->runAction(seq);

	PersonalAudioEngine::sharedEngine()->playEffect(kEffectShoot);
	_bulletSprite->setTag(p_bullet);
	_bulletSprite->setUserData(&_typeBullet);
	PHYSICS_WORLD_ADD_BODY_FOR_SPRITE(_bulletSprite);
}

void Bullet::spriteDone( CCObject *sender )
{
	PHYSICS_WORLD_SPRITE_DOWN(sender);
	stopAllActions();
	setVisible(false);
}

cocos2d::CCPoint Bullet::getCollisionPoint()
{
	return this->getParent()->convertToWorldSpace(getPosition());
}

CCSprite * Bullet::getBulletSprite()
{
	return _bulletSprite;
}

float Bullet::getBulletSpeed()
{
	switch(_typeBullet)
	{
	case 0: 
		return 500;
		break;
	case 1:
		return 600;
		break;
	case 2:
		return 700;
		break;
	case 3:
		return 800;
		break;
	case 4:
		return 900;
		break;
	case 5:
		return 1000;
		break;
	case 6:
		return 1200;
		break;
	}
}

float Bullet::getBulletPro()
{
	switch(_typeBullet)
	{
	case 0: 
		return 0.3f;
		break;
	case 1:
		return 0.4f;
		break;
	case 2: 
		return 0.5f;
		break;
	case 3:
		return 0.6f;
		break;
	case 4: 
		return 0.7f;
		break;
	case 5:
		return 0.8f;
		break;
	case 6: 
		return 1.0f;
		break;
	}
}
