#include "FishLayer.h"

#define BOXDEBOG false

FishLayer::FishLayer()
{

}

FishLayer::~FishLayer()
{
	CC_SAFE_RELEASE(_fishes);

}

bool FishLayer::init()
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		int capacity = 50;/////////////////////////////////////////////要改
		_fishes = CCArray::createWithCapacity(capacity);
		CC_SAFE_RETAIN(_fishes);

		for(int i = 0; i < capacity ; i++)
		{
			int type = CCRANDOM_0_1() * k_Fish_Type_Count - 1;
			//int type = 13;
			Fish* fish = Fish::create((FishType)type);
			_fishes->addObject(fish);
		}
		this->schedule(schedule_selector(FishLayer::addFish),3.0);
		//addFish(3);
		return true;
	} while (0);
	return false;

	/*if (!CCLayer::init())
	{	
		return false;
	}
	Fish *fish = Fish::create((FishType)0);
	addChild(fish);
	fish->setPosition(100,100);
	return true;*/
}

void FishLayer::addFish( float dt )
{

	int countToAdd = CCRANDOM_0_1()*10 + 1;
	if(countToAdd < 5)
		countToAdd = 5;
	//int countToAdd = 1;
	int countHasAdded = 0;
	CCObject* iterator;
	CCARRAY_FOREACH(_fishes, iterator)
	{
		Fish* fish = (Fish*)iterator;
		if(fish->getParent() == NULL)//////要改
		{
			this->addChild(fish);
			this->resetFish(fish);
			countHasAdded++;
			if(countToAdd == countHasAdded)
				break;
		}
	}
}

void FishLayer::resetFish( Fish *fish )
{
	fish->reset();
	CCPoint start,destination;
	float startX, startY, endX, endY;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize fishSize = fish->fishSize();
	int direction = CCRANDOM_0_1()*2;

	float maxSize = MAX(fishSize.width, fishSize.height);
	//maxSize *= 0.5;

	float slope;
	int flagX,flagY;
	slope = CCRANDOM_0_1()*(winSize.height/winSize.width);///斜率值
	float rotation = atan(slope) * 180/M_PI;//角度值//一开始的时候把180写成了360导致鱼的方向和运动方向不一致，随着slope的增大而误差增大，有的又没有误差，怪得很
	if(direction)
	{
		flagX = 1;
		startX = winSize.width + maxSize*0.5;
		endX = 0;
	}
	else
	{
		flagX = 0;
		startX = -maxSize*0.5;
		endX = winSize.width ;
	}

	startY = CCRANDOM_0_1()*(winSize.height - 2 * fishSize.height) + fishSize.height;

	if(startY >= winSize.height/2.0)
	{
		flagY = 1;
	}
	else
	{
		flagY = 0;
	}

	if(flagX == 0 && flagY == 0)
	{
		float y = slope * winSize.width + startY;
		if(y>winSize.height)
		{
			endY = winSize.height + maxSize*0.5;
			endX = (winSize.height - startY)/slope + maxSize*0.5;
		}
		else
		{
			endY = y + maxSize*0.5;
			endX = winSize.width + maxSize*0.5;
		}
		//fish->getFishSprite()->setRotation(180 - rotation);
	}
	else if(flagX ==1 && flagY ==0)
	{
		float y = startY + startX * slope;
		if(y>winSize.height)
		{
			endY = winSize.height + maxSize*0.5;
			endX = (y-winSize.height)/slope - maxSize*0.5;
		}
		else
		{
			endX = -maxSize*0.5;
			endY = y + maxSize*0.5;
		}
		//fish->getFishSprite()->setRotation(rotation);
	}
	else if(flagX ==0 && flagY == 1)
	{
		float y = -slope * winSize.width + startY;
		if(y < 0)
		{
			endY = - maxSize*0.5;
			endX = startY / slope + maxSize*0.5;
		}
		else
		{
			endX = winSize.width + maxSize*0.5;
			endY = y - maxSize*0.5;
		}
		//fish->getFishSprite()->setRotation(180 + rotation);
	}
	else if(flagX ==1 && flagY ==1)
	{
		float y = startY - startX * slope;
		if(y < 0)
		{
			endY = -maxSize*0.5;
			endX = (slope * startX - startY)/slope + maxSize*0.5;
		}
		else
		{
			endX = -maxSize * 0.5;
			endY = y + maxSize * 0.5;
		}
		//fish->getFishSprite()->setRotation(-rotation);
	}


	start = CCPointMake(startX,startY);
	//start = CCPointMake(-10,-10);
	destination = CCPointMake(endX,endY);
	//destination = CCPointMake(startX,startY);


	fish->setPosition(start);
	fish->bezierBy(start, destination);

	//fish->moveTo(destination);


	//测试发现精灵帧的getContentSize是根据plist里面sourceSize的值来决定的！,而 getTextureRect当前的纹理在总纹理的位置 
	//CCString *frameSpriteName = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_format"),"GMarlinsFish", 1);
	//CCSprite *rtt = CCSprite::createWithSpriteFrameName(frameSpriteName->getCString());
	////CCRect tt = rtt->getTextureRect();
	//CCSize tt =  rtt->getContentSize();
	//CCLog("%lf     %lf", tt./*size.*/width,tt./*size.*/height);
}

CCArray* FishLayer::getFishes()
{
	return _fishes;
}

void FishLayer::draw()
{
	CCLayer::draw();
	//glDisable(GL_TEXTURE_2D);  
	//glDisableClientState(GL_COLOR_ARRAY);  
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);  
	if(BOXDEBOG)
		PhySicsWorldFzj::sharedPhySicsWorldFzj()->getWorld()->DrawDebugData();
	//glEnable(GL_TEXTURE_2D);  
	//glEnableClientState(GL_COLOR_ARRAY);  
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);  
}
