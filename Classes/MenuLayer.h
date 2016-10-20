#pragma once
#include "cocos2d.h"
#include "FishingJoyData.h"

USING_NS_CC;
class GameScene;
class GameMenuLayer;
class MenuLayer : public CCLayer
{
public:
	MenuLayer();
	~MenuLayer();
	bool init();
	
	void resume(CCObject *sender);
	void soundOnAndOff(CCObject *sender);
	void musicOnAndOff(CCObject *sender);
	void mainMenu(CCObject *sender);
	void setSoundAndMusicVolume(float soundVolume, float musicVolume);
	CREATE_FUNC(MenuLayer);
protected:
	CCMenuItemToggle* _sound;
	CCMenuItemToggle* _music;
	
	void createBackgroud();
	void createMenu();
private:
};