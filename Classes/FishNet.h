#pragma once

#include "cocos2d.h"
#include "StaticData.h"
#include "PhysicsWorldFzj.h"
#include "PersonalAudioEngine.h"
USING_NS_CC;
class FishNet : public CCNode
{

public:
	FishNet();
	~FishNet();
	bool init();
	float getFireRange();
	void showAt(CCPoint pos,int type = 0);
	CCRect getCollisionArea();
	CREATE_FUNC(FishNet);

	CCSprite* getFishNetSprite();
	void end();
protected:
	CCSprite*  _fishNetSprite ;
private:

};