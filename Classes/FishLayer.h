#pragma once
#include "cocos2d.h"
#include "Fish.h"
#include "math.h"
USING_NS_CC;



#include "Box2D/Box2D.h"
#include "ContactListener.h"

class FishLayer : public CCLayer
{
public:
	FishLayer();
	~FishLayer();
	bool init();
	void addFish(float dt);
	void resetFish(Fish *fish);
	CCArray* getFishes();
	CREATE_FUNC(FishLayer);

	virtual void draw();

protected:
	CCArray* _fishes;


};