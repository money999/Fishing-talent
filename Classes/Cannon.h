#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;
typedef enum{
	k_Cannon_Type_1 = 0,
	k_Cannon_Type_2,
	k_Cannon_Type_3,
	k_Cannon_Type_4,
	k_Cannon_Type_5,
	k_Cannon_Type_6,
	k_Cannon_Type_7,
	k_Cannon_Count,
	//k_Cannon_Invalid
}CannonType;

class Cannon : public CCNode
{
	CC_PROPERTY(CannonType,_type,Type);
	CC_SYNTHESIZE_READONLY(CCArray *, _cannonSprites, CannonSprites);
public:
	static Cannon * create(CannonType type = k_Cannon_Type_1);
	Cannon();
	~Cannon();
	bool init(CannonType type = k_Cannon_Type_1);
	void aimAt(CCPoint target);
	void switchCallBack();
	void call_fun_cannon1();
	void call_fun_cannon2();

	int getCannonCost();
protected:
	CannonType _now;
};