#include "MenuLayer.h"
#include "GameScene.h"
#include "GameMenuLayer.h"

MenuLayer::MenuLayer()
{

}

MenuLayer::~MenuLayer()
{

}

bool MenuLayer::init()
{
	do 
	{
		createBackgroud();
		createMenu();
		//setTouchEnabled(true);
		
		return true;
	} while (0);
	return false;
}

void MenuLayer::createBackgroud()
{
	CCLayerColor* colorBackground = CCLayerColor::create(ccc4(0, 0, 0, 128));
	this->addChild(colorBackground);  
}

void MenuLayer::createMenu()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int fontSize=32;
	CCString *fontName = CCString::create("Thonburi");//字体的名称,没有用默认的
	CCMenuItemLabel* resumeItem = CCMenuItemLabel::create(CCLabelTTF::create("Resume", fontName->getCString(), fontSize), this, menu_selector(MenuLayer::resume));
	CCMenuItemLabel* soundOnItem = CCMenuItemLabel::create(CCLabelTTF::create("Sound On", fontName->getCString(), fontSize));
	CCMenuItemLabel* soundOffItem = CCMenuItemLabel::create(CCLabelTTF::create("Sound Off", fontName->getCString(), fontSize));
	CCMenuItemLabel* musicOnItem = CCMenuItemLabel::create(CCLabelTTF::create("Music On", fontName->getCString(), fontSize));
	CCMenuItemLabel* musicOffItem = CCMenuItemLabel::create(CCLabelTTF::create("Music Off", fontName->getCString(), fontSize));

	CCMenuItemFont::setFontName(fontName->getCString());//用静态成员来设置属性奇怪,一定要写在创建对象的前面
	CCMenuItemFont::setFontSize(32);
	CCMenuItemFont* mainMenuFont = CCMenuItemFont::create("Main Menu", this, menu_selector(MenuLayer::mainMenu));
	//mainMenuFont->setFontSize(60);

	
	_sound=CCMenuItemToggle::createWithTarget(this, menu_selector(MenuLayer::soundOnAndOff),soundOnItem, soundOffItem, NULL);
	_music=CCMenuItemToggle::createWithTarget(this, menu_selector(MenuLayer::musicOnAndOff),musicOnItem, musicOffItem, NULL);
	

	CCMenu *menu = CCMenu::create(resumeItem, mainMenuFont, _sound, _music, NULL);
	menu->setPosition(winSize.width * 0.5, winSize.height * 0.5);
	menu->alignItemsVerticallyWithPadding(50);

	setSoundAndMusicVolume(FishingJoyData::shareFishingJoyData()->getSoundVolume(), FishingJoyData::shareFishingJoyData()->getMusicVolume());
	addChild(menu);
}

void MenuLayer::resume(CCObject *sender )
{
	((GameScene*)this->getParent())->pauseAndContinue();
}

void MenuLayer::soundOnAndOff(CCObject *sender )
{
	switch (_sound->getSelectedIndex())
	{
	case 0:
		PersonalAudioEngine::sharedEngine()->setEffectsVolume(1);
		//PersonalAudioEngine::sharedEngine()->setSoundEnable(true);
		//FishingJoyData::shareFishingJoyData()->setSoundVolume(1);
		//FishingJoyData::shareFishingJoyData()->flush();
		break;
	case 1:
		PersonalAudioEngine::sharedEngine()->setEffectsVolume(0);
		//PersonalAudioEngine::sharedEngine()->setSoundEnable(false);
		//FishingJoyData::shareFishingJoyData()->setSoundVolume(0);
		//FishingJoyData::shareFishingJoyData()->flush();
		break;
	}
}

void MenuLayer::musicOnAndOff( CCObject *sender )
{
	switch (_music->getSelectedIndex())
	{
	case 0:
		PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
		//FishingJoyData::shareFishingJoyData()->setMusicVolume(1);
		//FishingJoyData::shareFishingJoyData()->flush();
		break;
	case 1:
		PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
		//FishingJoyData::shareFishingJoyData()->setMusicVolume(0);
		//FishingJoyData::shareFishingJoyData()->flush();
		break;
	}
}

void MenuLayer::setSoundAndMusicVolume( float soundVolume, float musicVolume )
{
	if(soundVolume == 0)
		_sound->setSelectedIndex(1);
	if(musicVolume == 0)
		_music->setSelectedIndex(1);
}

void MenuLayer::mainMenu( CCObject *sender )
{
	PhySicsWorldFzj::destroyWorld();

	CCTransitionScene * reScene = NULL;
	CCScene *temp = GameMenuLayer::scene();
	float t = 1.2f;
	reScene = CCTransitionShrinkGrow::create(t, temp);
	CCDirector::sharedDirector()->replaceScene(reScene);
	//CCDirector::sharedDirector()->replaceScene(temp);
}

