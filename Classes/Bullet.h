#pragma once

#include "cocos2d.h"
#include "StaticData.h"
#include "FishNet.h"
#include "PhysicsWorldFzj.h"
#include "PersonalAudioEngine.h"
USING_NS_CC;
class Bullet : public CCNode
{

public:
	Bullet();
	~Bullet();
	bool init();
	void end();
	void flyTo(CCPoint targetInWordSpace, int type/*=0*/, CCSize cannonSize);
	CCPoint getCollisionPoint();
	CCSprite *getBulletSprite();
	
	void spriteDone( CCObject *sender );

	float getBulletSpeed();
	float getBulletPro();

	CREATE_FUNC(Bullet);

	
protected:

	CCSprite* _bulletSprite;

	int _typeBullet;
private:

};