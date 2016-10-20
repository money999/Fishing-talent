#pragma once
#include "cocos2d.h"
#include "FishNet.h"
#include "Bullet.h"
#include "Cannon.h"
typedef enum{
	k_Cannon_Operate_Up = 1,
	k_Cannon_Operate_Down = -1
}CannonOperate;

USING_NS_CC;

#define BULLET_COUNTS 10
class Weapon : public CCNode
{
	CC_SYNTHESIZE_READONLY(Cannon *, _cannon, CannonValue);
public:
	Weapon();
	~Weapon();
	CCSize getCannonSize();
	static Weapon* create(CannonType type = k_Cannon_Type_1);
	bool init(CannonType type = k_Cannon_Type_1);
	void changeCannon(CannonOperate operate);
	void aimAt(CCPoint target);
	void shootTo (CCPoint target);
	Bullet* getBulletToShoot();
	CCArray* getBullets();
	void end(Bullet *bullet);
	CCRect getCollisionArea(Bullet *bullet);
protected:
	//Cannon* _cannon;
	CCArray* _bullets;
	CCArray* _fishNets;

	CCArray* _particles;
private:

};


