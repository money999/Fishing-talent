#pragma once
#include "cocos2d.h"//�����ÿ��ӻ���ide���ڷž�̬��ͼƬ
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

