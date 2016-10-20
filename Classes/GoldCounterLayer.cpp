#include "GoldCounterLayer.h"
#define COUNTER_NUM 7


GoldCounterLayer::GoldCounterLayer()
{

}

GoldCounterLayer::~GoldCounterLayer()
{

}

GoldCounterLayer* GoldCounterLayer::create( int number /*= 1314520*/ )
{
	GoldCounterLayer *gold = new GoldCounterLayer();
	gold->autorelease();
	gold->init(number);
	return gold;
}

bool GoldCounterLayer::init(int number)
{
	int fontSize=28;
	CCString *fontName = CCString::create("Thonburi");//字体的名称,没有用默认的
	int i,j;

	/*CCTexture2D * texture2d = CCTextureCache::sharedTextureCache()->addImage("");
	CCRect rect = CCRectMake(j*26, 0, 26, 34);
	CCSprite * sprite = CCSprite::createWithTexture(texture2d, rect);*/

	for(i=0;i<COUNTER_NUM;i++)
	{
		CCArray *num =  CCArray::createWithCapacity(10);
		for(j=0;j<10;j++)
		{
			CCLabelTTF *t = CCLabelTTF::create(CCString::createWithFormat("%d",j)->getCString(), fontName->getCString(), fontSize);
			t->setColor(ccBLACK);
			num->addObject(t);
		}
		Counter *counter = Counter::create(num, 0);
		float x = 25.3f * i;
		counter->setPosition(x, 0);
		addChild(counter, 0, i);
	}

	this->setNumber(number);
	return true;
}

void GoldCounterLayer::setNumber( int number, int ceiling /*= 9999999*/ )
{
	if(number>=0 && number<=ceiling)
	{
		_number = number;
		int t,i = COUNTER_NUM - 1;
		while(i>-1)
		{
			t = number % 10;
			Counter * tc = (Counter*)getChildByTag(i);
			if(tc != NULL)
			{
				tc->setDigit(t);
			}
			i--;
			number /= 10;
		}
	}
}
