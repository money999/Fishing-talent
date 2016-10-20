#pragma once

#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class FishingJoyData : public CCObject
{
	CC_SYNTHESIZE(int , _gold, Gold);
	CC_SYNTHESIZE(bool, _isBeginner, IsBeginner);
	CC_SYNTHESIZE(float, _soundVolume, SoundVolume);
	CC_SYNTHESIZE(float, _musicVolume, MusicVolume);
public:
	static FishingJoyData* shareFishingJoyData();
	static void purge();

	FishingJoyData();
	~FishingJoyData();
	 
	bool init();
	void flush();
	void reset();
	void alterGold(int delta);


protected:


private:

};

//#define DYNAMIC_DATA_