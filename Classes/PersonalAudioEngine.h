#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "FishingJoyData.h"
#include "StaticData.h"
USING_NS_CC;

typedef enum{
	kEffectSwichCannonLeft = 0,
	kEffectSwichCannonRight,
	kEffectShoot,
	kEffectFishNet,
	kEffectCoins,
	kEffectSnapshot
}EffectType;

class PersonalAudioEngine : public CocosDenshion::SimpleAudioEngine
{
	CC_SYNTHESIZE(bool, _soundEnable, SoundEnable);//µ˜ ‘ ±∫Ú”√
public:
	static PersonalAudioEngine* PersonalAudioEngine::sharedEngine();
	static void purge();

	bool init();
	void setBackgroundMusicVolume(float volume);
	void setEffectsVolume(float volume);
	void playBackgroundMusic(int type);
	void playEffect(EffectType type);

protected:
private:
	PersonalAudioEngine();
	~PersonalAudioEngine();
};