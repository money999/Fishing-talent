#include "LoadingLayer.h"
#include "GameScene.h"
LoadingLayer::LoadingLayer()
{
	_loadedSp = 0;
	_numSp = 100;
	_progressBar = NULL;
	_progressFg = NULL;
}

LoadingLayer::~LoadingLayer()
{

}

bool LoadingLayer::init(int type)
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		_type = type;
		CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
		textureCache->addImage(STATIC_DATA_STRING("loading_1"));
		textureCache->addImage(STATIC_DATA_STRING("loading_4"));
		textureCache->addImage(STATIC_DATA_STRING("loading_5"));
		CCLayer::init();
		//2．	添加背景
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *imageBg = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("loading_1")));
		imageBg->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.7));
		addChild(imageBg);
		initProgressBar();
		cacheInit();
		return true;
	} while (0);
	return false;
}


void LoadingLayer::initProgressBar()
{
	CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
	CCSprite *progressBg = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("loading_4")));
	CCSprite *progressb = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("loading_5")));
	int fontSize=28;
	CCString *fontName = CCString::create("Thonburi");
	_progressFg = CCLabelTTF::create("0/100", fontName->getCString(), fontSize);
	_progressBar = ProgressBar::create(this, progressb);
	_progressBar->setBackground(progressBg);
	_progressBar->setForeground(_progressFg);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_progressBar->setPosition(winSize.width * 0.5, winSize.height * 0.4);
	addChild(_progressBar);
}

void LoadingLayer::loadingFinished()
{
	//cacheInit();
	//CCTransitionFadeDown *gameScene = CCTransitionFadeDown::create(1.0f,GameScene::create());

	PersonalAudioEngine::sharedEngine();
	animNum = 0;
	schedule(schedule_selector(LoadingLayer::loadAnim));
}

void LoadingLayer::progressPercentageSetter( float percentage )
{
	CCString *str = CCString::createWithFormat("%d/100",(int)percentage);
	_progressFg->setString(str->getCString());
}


void LoadingLayer::loadAnim(float delta)
{
	
	loadAnimSub(animNum);
	animNum++;
	_progressBar->progressByAnim(3);
	float tmp = _progressBar->getPercentage();
	if(animNum == k_Fish_Type_Count)
	{
		unschedule(schedule_selector(LoadingLayer::loadAnim));
		//CCLog("rrrrrrrrrrrrrrrrrrrrrrr");
		schedule(schedule_selector(LoadingLayer::launchGame),0,0,0.1f);
	}
}


void LoadingLayer::loadAnimSub(int i)
{
	PersonalAudioEngine::sharedEngine();
	int frameCount = STATIC_DATA_INT("fish_frame_count");
	char str[][50] = {"SmallFish","Croaker","AngelFish","Amphiprion","PufferS","Bream","Porgy","Chelonian","Lantern","Ray","Shark","GoldenTrout","GShark","GMarlinsFish","GrouperFish","JadePerch","MarlinsFish","PufferB"};
	//for(int i = k_Fish_Type_SmallFish; i<k_Fish_Type_Count; i++)
	//{
		CCArray *array = CCArray::createWithCapacity(frameCount);
		for(int j= 0;j<frameCount;j++)
		{
			CCString *frameSpriteName = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_format"),str[i],j + 1);
			CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameSpriteName->getCString());
			CC_BREAK_IF(!spriteFrame);
			array->addObject(spriteFrame);
		}
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(array);
		animation->setDelayPerUnit(STATIC_DATA_FLOAT("fish_frame_delay"));
		CCString *animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation_format"),i);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation,animationName->getCString());
	//}
}


void LoadingLayer::cacheInit()
{
	//1、只有png：用addImageAsync（。png，this，回调）;
	//2、有plist+png
	//动画一定要在进度条后面做完

	//就5个plist命名规则是从1-5

	for(int i=1; i<=5; i++)
	{
		const char * temp = STATIC_DATA_STRING(CCString::createWithFormat("fish_plist_%02d",i)->getCString());
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(temp);
	}
	CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();

	textureCache->addImageAsync("cannon.png", this, callfuncO_selector(LoadingLayer::loading1));
	textureCache->addImageAsync("Item-chaojiwuqi.png", this, callfuncO_selector(LoadingLayer::loading2));
	textureCache->addImageAsync("UI_GameMenuLayer-ipadhd.png", this, callfuncO_selector(LoadingLayer::loading3));
	
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("cannon_plist"));
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("bullet_plist"));
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("menulayer_plist"));

	textureCache->addImageAsync(STATIC_DATA_STRING("button_add"), this,callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync(STATIC_DATA_STRING("button_sub"), this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync(STATIC_DATA_STRING("button_music_normal"), this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync(STATIC_DATA_STRING("button_music_selected"), this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync(STATIC_DATA_STRING("button_photo_normal"), this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync(STATIC_DATA_STRING("button_photo_selected"), this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync(STATIC_DATA_STRING("button_fish_normal"), this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync(STATIC_DATA_STRING("button_fish_selected"), this, callfuncO_selector(LoadingLayer::loading));

	for(int i = 1; i<= 4; i++)
	{
		CCString *tt = CCString::createWithFormat(STATIC_DATA_STRING("button_prop_format"), i);
		textureCache->addImageAsync(tt->getCString(), this,callfuncO_selector(LoadingLayer::loading));
	}

	textureCache->addImageAsync(STATIC_DATA_STRING("gold_box"), this, callfuncO_selector(LoadingLayer::loading));

	textureCache->addImageAsync(STATIC_DATA_STRING("prizesign"), this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync(STATIC_DATA_STRING("prizenum"), this, callfuncO_selector(LoadingLayer::loading));

	for(int i = 1; i<= 4; i++)
	{
		CCString *tt = CCString::createWithFormat(STATIC_DATA_STRING("count_down_three"), i);
		textureCache->addImageAsync(tt->getCString(), this,callfuncO_selector(LoadingLayer::loading));
	}

	/*textureCache->addImage(STATIC_DATA_STRING("button_add"));
	textureCache->addImage(STATIC_DATA_STRING("button_sub"));
	textureCache->addImage(STATIC_DATA_STRING("button_music_normal"));
	textureCache->addImage(STATIC_DATA_STRING("button_music_selected"));
	textureCache->addImage(STATIC_DATA_STRING("button_photo_normal"));
	textureCache->addImage(STATIC_DATA_STRING("button_photo_selected"));
	textureCache->addImage(STATIC_DATA_STRING("button_fish_normal"));
	textureCache->addImage(STATIC_DATA_STRING("button_fish_selected"));*/

}

void LoadingLayer::loading( CCObject *sender )
{
	_progressBar->progressBy(2);
}

void LoadingLayer::loading1( CCObject *sender )
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("cannon_plist"), (CCTexture2D *)sender);
	_progressBar->progressBy(3);
}

void LoadingLayer::loading2( CCObject *sender )
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("bullet_plist"), (CCTexture2D *)sender);
	_progressBar->progressBy(3);
}

void LoadingLayer::loading3( CCObject *sender )
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("menulayer_plist"), (CCTexture2D *)sender);
	_progressBar->progressBy(2);
}

CCScene* LoadingLayer::scene(int type)
{
	CCScene *scene = CCScene::create();
	LoadingLayer *layer = LoadingLayer::create(type);
	scene->addChild(layer);	
	return scene;
}

void LoadingLayer::launchGame(float delta)
{
	CCTransitionScene * reScene = NULL;
	GameScene *temp = GameScene::create(_type);
	float t = 1.2f;
	reScene = CCTransitionTurnOffTiles::create(t, temp);
	CCDirector::sharedDirector()->replaceScene(reScene);
	//CCDirector::sharedDirector()->replaceScene(temp);
}

LoadingLayer * LoadingLayer::create( int type )
{
	LoadingLayer *tt = new LoadingLayer();
	tt->init(type);
	tt->autorelease();
	return tt;
}





