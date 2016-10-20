#include "FishingJoyData.h"

static FishingJoyData *g_sharedFishingJoyData = NULL;



FishingJoyData* FishingJoyData::shareFishingJoyData()
{
	if(g_sharedFishingJoyData == NULL)
	{
		g_sharedFishingJoyData = new FishingJoyData();
		g_sharedFishingJoyData->init();
	}
	return g_sharedFishingJoyData;
}

void FishingJoyData::purge()
{
	CC_SAFE_DELETE(g_sharedFishingJoyData);
}


FishingJoyData::FishingJoyData()
{

}

FishingJoyData::~FishingJoyData()
{

}

bool FishingJoyData::init()
{
	_isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner",true);//这些要用宏来写
	if(_isBeginner)
	{
		reset();
		flush();
		_isBeginner = false;
	}
	else
	{
		_gold = CCUserDefault::sharedUserDefault()->getIntegerForKey("gold");
		_soundVolume = CCUserDefault::sharedUserDefault()->getIntegerForKey("soundVolume");
		_musicVolume = CCUserDefault::sharedUserDefault()->getIntegerForKey("musicVolume");
	}
	return true;
}

void FishingJoyData::flush()
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("beginner",_isBeginner);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("gold",_gold);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("soundVolume",_soundVolume);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("musicVolume",_musicVolume);
	CCUserDefault::sharedUserDefault()->flush();
}

void FishingJoyData::reset()
{
	setGold(STATIC_DATA_INT("default_gold"));
	setIsBeginner(true);
	setSoundVolume(1);
	setMusicVolume(1);
}

void FishingJoyData::alterGold( int delta )
{
	int goldNum = getGold();
	goldNum += delta;
	setGold(goldNum);
}
