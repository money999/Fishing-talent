#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "PhysicsWorldFzj.h"
#include "BezierFzj.h"
USING_NS_CC;
using namespace std;

typedef enum{
	k_Fish_Type_SmallFish = 0,
	
	k_Fish_Type_Croaker,
	k_Fish_Type_AngelFish,
	k_Fish_Type_Amphiprion,	//小丑鱼3
	k_Fish_Type_PufferS,	//刺豚4
	k_Fish_Type_Bream,		//蓝色
	k_Fish_Type_Porgy,		//红色
	k_Fish_Type_Chelonian,	//乌龟7
	k_Fish_Type_Lantern,	//灯笼鱼8
	k_Fish_Type_Ray,		//魔鬼鱼9
	k_Fish_Type_Shark,		//蓝色鲨鱼10
	k_Fish_Type_GoldenTrout,
	k_Fish_Type_GShark,		//金色鲨鱼
	k_Fish_Type_GMarlinsFish,     //13
	k_Fish_Type_GrouperFish,
	k_Fish_Type_JadePerch,	//宝石鱼
	k_Fish_Type_MarlinsFish,
	k_Fish_Type_PufferB,	//刺豚受到攻击 17 共18头鱼
	k_Fish_Type_Count,//鱼的数量，可以根据测试的需要调整位置，在这里值是2
	//k_Fish_Type_Count
}FishType;

enum{
	k_Action_Animate = 0,
	k_Action_MoveTo
};

enum{
	k_Fish_Tag = 0
};

class Fish : public CCNode
{
	CC_SYNTHESIZE_READONLY(CCSprite*,_fishSprite,FishSprite);
	CC_SYNTHESIZE_READONLY(FishType,_type,Type);
	CC_SYNTHESIZE(bool, _isCaught, IsCaught);
public:
	Fish();
	~Fish();
	bool init(FishType type = k_Fish_Type_SmallFish);
	static Fish* create(FishType type = k_Fish_Type_SmallFish);
	
	

	void reset();
	void moveTo(cocos2d::CCPoint destination);
	void bezierBy(CCPoint startP, CCPoint endP);
	void moveEnd();

	CCRect getCollisionArea();
	void beCaught();
	void beCaught_CallFunc();
	void createPhysicsBody();
	CCSize fishSize();

	float getSpeed();

	int getFishGold();
	float getBezierTime();
	float getControlHeigth();
	float getFishPro();
	//virtual void draw();
protected:
private:
};
