#include "GameMenuLayer.h"
#include "GameMenuScene.h"
GameMenuLayer::GameMenuLayer()
{

}

GameMenuLayer::~GameMenuLayer()
{

}

bool GameMenuLayer::init()
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		/*gui::TouchGroup* ul = gui::TouchGroup::create();
		ul->addWidget(GUIReader::shareReader()->widgetFromJsonFile("startMenu_1/startMenu_1.json"));
		this->addChild(ul);
		ActionObject* action1=ActionManager::shareManager()->getActionByName("SampleUIAnimation.ExportJson","Animation1"); 
		action1->play();*/
		

		CCSprite * sp = CCSprite::create(STATIC_DATA_STRING("game_menu_background"));
		sp->setPosition(ccp(winSize.width/2, winSize.height/2));
		//CCActionInterval * ripple3D= CCRipple3D::create(50,CCSize(30,30),CCPointMake(winSize.width/2, winSize.height/2),600,50,50.0f);
		CCActionInterval * ripple3D = CCLiquid::create(99, CCSize(160, 120), 30, 2.0f);
		sp->runAction(ripple3D);
		addChild(sp);

		CCNode *node = SceneReader::sharedSceneReader()->createNodeWithSceneFile("FishJoy2.json");//上课上机的地方不能用SceneReader，会找不到，要改用CCSSceneReader,后发现2.2.0要ccs2.2.5不要且一定不能要
		addChild(node);

		/*CCSprite *bkSprite = CCSprite::create(STATIC_DATA_STRING(""));
		CC_BREAK_IF(!bkSprite);
		bkSprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
		addChild(bkSprite);*/


		CCSprite *tlSprite = CCSprite::create(STATIC_DATA_STRING("game_menu_title"));
		CC_BREAK_IF(!tlSprite);
		tlSprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.8));
		addChild(tlSprite);
		createMenu();
		return true;
	} while (0);
	return false;
}

CCScene * GameMenuLayer::scene()
{
	CCScene* tempScene = CCScene::create();
	GameMenuLayer* tempGameMenuLayer = GameMenuLayer::create();
	tempScene->addChild(tempGameMenuLayer);
	return tempScene;
}

void GameMenuLayer::createMenu()
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI_GameMenuText_cn.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI_GameStartMenuLayer.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("game_menu_text"));
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("game_menu_ui"));


	/*CCSprite *startNormalBKSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_normal"));
	CCSprite *startSelectedBKSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_selected"));
	CCSprite *startNormalTextSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_text"));
	CCSprite *startSelectedTextSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("game_menu_start_text"));

	startNormalBKSprite->addChild(startNormalTextSprite);
	startNormalTextSprite->setPositionX(startNormalBKSprite->getContentSize().width * 0.5);
	startNormalTextSprite->setPositionY(startNormalBKSprite->getContentSize().height * 0.5);

	startSelectedBKSprite->addChild(startSelectedTextSprite);
	startSelectedTextSprite->setPositionX(startSelectedBKSprite->getContentSize().width * 0.5);
	startSelectedTextSprite->setPositionY(startSelectedBKSprite->getContentSize().height * 0.5);*/

	SpriteButtonFzj* startItem = SpriteButtonFzj::create();
	startItem->setImage("game_menu_start_normal","game_menu_start_selected","game_menu_start_text","game_menu_start_text");
	startItem->setOffset(0.5f,0.57f,0.5f,0.57f);
	SpriteButtonFzj* sceneItem = SpriteButtonFzj::create();
	sceneItem->setImage("game_menu_scene_normal","game_menu_scene_selected","game_menu_scene_text","game_menu_scene_text");
	sceneItem->setOffset(0.5f,0.5f,0.5f,0.5f);

	CCMenuItemSprite *startMenuItem = CCMenuItemSprite::create(startItem->getNormalBKSprite(),startItem->getSelectedBKSprite(),this,menu_selector(GameMenuLayer::menuCallbackStartGame));
	CCMenuItemSprite *sceneMenuItem = CCMenuItemSprite::create(sceneItem->getNormalBKSprite(),sceneItem->getSelectedBKSprite(),this,menu_selector(GameMenuLayer::menuCallbackSelectScene));
	CCMenuItemSprite *buttonMy = CCMenuItemSprite::create(CCSprite::create(STATIC_DATA_STRING("menuButtonMy")),CCSprite::create(STATIC_DATA_STRING("menuButtonMy")),this, menu_selector(GameMenuLayer::menuCallbackButtonMy));

	CCMenu *menu = CCMenu::create(startMenuItem, sceneMenuItem, buttonMy ,NULL);
	menu->alignItemsVerticallyWithPadding(50);
	this->addChild(menu);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	menu->setPosition(ccp(winSize.width*0.5,winSize.height*0.3));

}

void GameMenuLayer::menuCallbackStartGame( CCObject *sender )
{

	CCTransitionScene * reScene = NULL;
	CCScene *temp = LoadingLayer::scene(1);
	float t = 1.2f;
	reScene = CCTransitionCrossFade::create(t, temp);
	//CCDirector::sharedDirector()->replaceScene(reScene);
	CCDirector::sharedDirector()->replaceScene(temp);
}

void GameMenuLayer::menuCallbackSelectScene( CCObject *sender )
{
	CCTransitionScene * reScene = NULL;
	WhereScene *temp = WhereScene::create();
	float t = 1.2f;
	reScene = CCTransitionProgressInOut::create(t, temp);
	CCDirector::sharedDirector()->replaceScene(reScene);
	//CCDirector::sharedDirector()->replaceScene(temp);
}

void GameMenuLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	PersonalAudioEngine::sharedEngine()->playBackgroundMusic(1);
}

void GameMenuLayer::menuCallbackButtonMy( CCObject *sender )
{
	GameMenuScene *tt = (GameMenuScene *)this->getParent();
	tt->addPopup();
}



