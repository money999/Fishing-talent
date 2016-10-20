#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	StaticData::purge();
	PhySicsWorldFzj::purge();
	FishingJoyData::purge();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->end();
	PersonalAudioEngine::sharedEngine()->end();
	PersonalAudioEngine::purge();
	
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();//精灵被多个父容器嵌套包含的时候的世界坐标zhiyao getparent就可以了//2、做了box2d的实验，做了将physicsWorldFzj封装好的实验，不过physicsWorldFzj已被改，故要用原来的注释（未封装box2d）helloworld才能跑起来
	//CCScene *pScene = GameScene::create();

	CCScene *pScene = GameMenuScene::create();

	//CCScene *pScene = LoadingLayer::scene();

	//CCScene * pScene  = CCScene::create(); 
	
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::debugfzj()
{
	int gold = FishingJoyData::shareFishingJoyData()->getGold();
	int mm = FishingJoyData::shareFishingJoyData()->getMusicVolume();
	int tt = FishingJoyData::shareFishingJoyData()->getSoundVolume();
	CCLog("%d  %d  %d", gold, mm, tt);
	FishingJoyData::shareFishingJoyData()->setGold(200);
	FishingJoyData::shareFishingJoyData()->flush();
	CCLog("%d  %d  %d", gold, mm, tt);

	gold = FishingJoyData::shareFishingJoyData()->getGold();
	mm = FishingJoyData::shareFishingJoyData()->getMusicVolume();
	tt = FishingJoyData::shareFishingJoyData()->getSoundVolume();
	CCLog("%d  %d  %d", gold, mm, tt);






	/*int gold = StaticData::sharedStaticData()->intFromKey("default_gold");
	CCLOG("GOLD = %d",gold);

	CCPoint point = StaticData::sharedStaticData()->pointFromKey("point");
	CCLOG("point = { %f, %f}",point.x,point.y);

	CCLOG("string = %s", StaticData::sharedStaticData()->stringFromKey("string"));

	CCSize size = StaticData::sharedStaticData()->sizeFromKey("size");
	CCLOG("size = {%f, %f}",size.width, size.height);
	CCRect rect = StaticData::sharedStaticData()->rectFromKey("rect");
	CCLOG("rect = {{%f, %f},{%f, %f}}",rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);*/


}
