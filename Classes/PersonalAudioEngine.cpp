#include "PersonalAudioEngine.h"

static PersonalAudioEngine *_shareEngine = NULL;

PersonalAudioEngine::PersonalAudioEngine()
{
	_soundEnable = true;
}

PersonalAudioEngine::~PersonalAudioEngine()
{

}

PersonalAudioEngine* PersonalAudioEngine::sharedEngine()
{
	if(_shareEngine == NULL)
	{
		_shareEngine = new PersonalAudioEngine();
		_shareEngine->init();
	}
	return _shareEngine;
}

void PersonalAudioEngine::purge()
{
	CC_SAFE_DELETE(_shareEngine);
}

bool PersonalAudioEngine::init()
{
	for(int i=1; i<=6; i++)
	{
		CCString *str = CCString::createWithFormat(STATIC_DATA_STRING("bg_music"),i);
		SimpleAudioEngine::preloadBackgroundMusic(str->getCString());
	}
	SimpleAudioEngine::preloadEffect(STATIC_DATA_STRING("button_music"));
	SimpleAudioEngine::preloadEffect(STATIC_DATA_STRING("bom_music"));
	SimpleAudioEngine::preloadEffect(STATIC_DATA_STRING("cannon_music_left"));
	SimpleAudioEngine::preloadEffect(STATIC_DATA_STRING("cannon_music_right"));
	SimpleAudioEngine::preloadEffect(STATIC_DATA_STRING("coin_music"));
	SimpleAudioEngine::preloadEffect(STATIC_DATA_STRING("fire_music"));
	SimpleAudioEngine::preloadEffect(STATIC_DATA_STRING("net_music"));
	SimpleAudioEngine::preloadEffect(STATIC_DATA_STRING("snap_music"));

	
	SimpleAudioEngine::setBackgroundMusicVolume(FishingJoyData::shareFishingJoyData()->getMusicVolume());
	SimpleAudioEngine::setEffectsVolume(FishingJoyData::shareFishingJoyData()->getSoundVolume());
	return true;
}

void PersonalAudioEngine::setBackgroundMusicVolume( float volume )
{
	SimpleAudioEngine::setBackgroundMusicVolume(volume);
	FishingJoyData::shareFishingJoyData()->setMusicVolume(volume);
	FishingJoyData::shareFishingJoyData()->flush();
}

void PersonalAudioEngine::setEffectsVolume( float volume )
{
	SimpleAudioEngine::setEffectsVolume(volume);
	FishingJoyData::shareFishingJoyData()->setSoundVolume(volume);
	FishingJoyData::shareFishingJoyData()->flush();
}

void PersonalAudioEngine::playBackgroundMusic( int type )
{
	CCString *str = CCString::createWithFormat(STATIC_DATA_STRING("bg_music"),type);
	SimpleAudioEngine::playBackgroundMusic(str->getCString(), true);
}

void PersonalAudioEngine::playEffect( EffectType type )
{
	if(_soundEnable){
		switch (type)
		{
		case kEffectSwichCannonLeft:
			SimpleAudioEngine::playEffect(STATIC_DATA_STRING("cannon_music_left"));
			break;
		case kEffectSwichCannonRight:
			SimpleAudioEngine::playEffect(STATIC_DATA_STRING("cannon_music_right"));
			break;
		case kEffectShoot:
			SimpleAudioEngine::playEffect(STATIC_DATA_STRING("fire_music"));
			break;
		case kEffectFishNet:
			SimpleAudioEngine::playEffect(STATIC_DATA_STRING("net_music"));
			break;
		case kEffectCoins:
			SimpleAudioEngine::playEffect(STATIC_DATA_STRING("coin_music"));
			break;
		case kEffectSnapshot:
			SimpleAudioEngine::playEffect(STATIC_DATA_STRING("snap_music"));
			break;
		}
	}
}
