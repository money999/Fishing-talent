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
	k_Fish_Type_Amphiprion,	//С����3
	k_Fish_Type_PufferS,	//����4
	k_Fish_Type_Bream,		//��ɫ
	k_Fish_Type_Porgy,		//��ɫ
	k_Fish_Type_Chelonian,	//�ڹ�7
	k_Fish_Type_Lantern,	//������8
	k_Fish_Type_Ray,		//ħ����9
	k_Fish_Type_Shark,		//��ɫ����10
	k_Fish_Type_GoldenTrout,
	k_Fish_Type_GShark,		//��ɫ����
	k_Fish_Type_GMarlinsFish,     //13
	k_Fish_Type_GrouperFish,
	k_Fish_Type_JadePerch,	//��ʯ��
	k_Fish_Type_MarlinsFish,
	k_Fish_Type_PufferB,	//�����ܵ����� 17 ��18ͷ��
	k_Fish_Type_Count,//������������Ը��ݲ��Ե���Ҫ����λ�ã�������ֵ��2
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
