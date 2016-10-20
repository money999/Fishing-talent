#pragma once
#include "cocos2d.h"//可以用可视化的ide来摆放静态的图片
#include "StaticData.h"
#include "Cannon.h"
USING_NS_CC;
using namespace std;
class BackgroundLayer : public CCLayer
{
public:
	BackgroundLayer();
	~BackgroundLayer();
	
	static BackgroundLayer *create(const char* strBackground);

	virtual bool init(const char* strBackground);
	//CREATE_FUNC(BackgroundLayer);
};

