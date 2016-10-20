#include "GoldShow.h"


GoldShow::GoldShow()
{

}

GoldShow::~GoldShow()
{

}

bool GoldShow::init(int num)
{
	do 
	{
		CC_BREAK_IF(!CCNode::init());
		if(num > 0 && num <= 5000)
		{
			int t, i=0, j=0;
			int aa[9];
			while(num)
			{
				t = num % 10;
				aa[i++] = t;
				num /= 10;
			}
			CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
			while(j<i)
			{
				CCRect rectNum(aa[j]*43.5, 0, 43.5, 50);
				CCSprite* sp = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("prizenum")), rectNum);
				sp->setPosition(ccp((i-j)*43.5, 0));
				j++;
				addChild(sp);
			}
			CCSprite* spSign = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("prizesign")));
			spSign->setPosition(ccp(0, 0));
			addChild(spSign);
		}
		return true;
	} while (0);
	return false;
}

GoldShow* GoldShow::create( int num )
{
	GoldShow *tt = new GoldShow();
	tt->init(num);
	tt->autorelease();
	return tt;
}
