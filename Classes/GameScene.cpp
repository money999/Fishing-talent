#include "GameScene.h"


GameScene* GameScene::create( int type )
{
	GameScene *tt = new GameScene();
	tt->init(type);
	tt->release();
	return tt;
}


bool GameScene::init(int type)
{
	preloadResources();
	scheduleUpdate();//����ĻƵ��һ����ÿ֡����update
	do
	{
		CC_BREAK_IF(!CCScene::init());
		_type = type;
		mTestDraw = new GLESDebugDraw(PTM_RATIO);
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		mTestDraw->SetFlags(flags);
		PhySicsWorldFzj::sharedPhySicsWorldFzj()->getWorld()->SetDebugDraw(mTestDraw);

		CCString *str = CCString::createWithFormat(STATIC_DATA_STRING("game_background"), type);
		_backgroudLayer = BackgroundLayer::create(str->getCString());
		CC_BREAK_IF(!_backgroudLayer);
		addChild(_backgroudLayer);

		_fishLayer = FishLayer::create();
		CC_BREAK_IF(!_fishLayer);
		addChild(_fishLayer);

		//Node* node = CSLoader::createNode("ActionTest/MainScene.csb");  //�������Ҫ��cc3.3���ϲ����ã��ʸ���cocostudio1.5��ԭ��2.2��
		//this->addChild(node);

		//SceneReader::createNodeWithSceneFile("mytest.json");
		//CCNode *node = SceneReader::sharedSceneReader()->createNodeWithSceneFile("NewScene.json"); //�����������ʧ�ܣ����б�������
		//addChild(node);

		///�ձ���
		/*gui::TouchGroup* ul = gui::TouchGroup::create();
		ul->addWidget(GUIReader::shareReader()->widgetFromJsonFile("NewUi_1/NewUi_1.ExportJson"));
		this->addChild(ul);*/

		
		gui::TouchGroup* ul = gui::TouchGroup::create();//cocos2dx-2.2.0�ǲ����õ�
		ul->addWidget(GUIReader::shareReader()->widgetFromJsonFile("SampleUIAnimation/SampleUIAnimation.ExportJson"));
		this->addChild(ul);
		ActionObject* action1=ActionManager::shareManager()->getActionByName("SampleUIAnimation.ExportJson","Animation1");
		action1->play();//������ΪUI�����õ�Action����cocos2d�Դ�����Щ����������������Ժ󣬻�ȥ����cocos2dԭ����stop����Ϊû��Action���Ծ�������~ cocos2d: removeAction: Target not found
		                //http://www.yiwuye.com/archives/cocostudio-ui-bug-rewrite.html  3.�����ع�����˵��

		_cannonLayer = CannonLayer::create();
		addChild(_cannonLayer);

		_paneLayer = PaneLayer::create();
		int goldNum = FishingJoyData::shareFishingJoyData()->getGold();
		_paneLayer->getGoldCounterLayer()->setNumber(goldNum);//���numʧ�ܾ���1314520
		addChild(_paneLayer);

		_menuLayer = MenuLayer::create();
		_menuLayer->setTag(MENU_LAYER_TAG);
		CC_SAFE_RETAIN(_menuLayer);

		_goldShowLayer = GoldShowLayer::create();
		addChild(_goldShowLayer);

		_touchLayer = TouchLayer::create();
		addChild(_touchLayer);

		///////////////��Ķ���/////////////   �Ѿ����ֿ����ں���UI�༭������
		/*CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("NewAnimation/NewAnimation.ExportJson");
		CCArmature* armature = CCArmature::create("NewAnimation");
		armature->getAnimation()->playByIndex(0);
		armature->setPosition(CCPoint(0, 0));
		armature->setScale(3.0f);
		this->addChild(armature); */ 
		for(int i=0;i<4;i++)
			showCountDown(i);
		return true;
	}while(0);
	return false;
}


GameScene::GameScene()
{
	_nowRunStatus = k_Operate_Resume;
}

GameScene::~GameScene()
{
	CC_SAFE_RELEASE(_menuLayer);
}

void GameScene::preloadResources()
{
	//��5��plist���������Ǵ�1-5
	for(int i=1; i<=5; i++)
	{
		const char * temp = STATIC_DATA_STRING(CCString::createWithFormat("fish_plist_%02d",i)->getCString());
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(temp);
	}
	
	int frameCount = STATIC_DATA_INT("fish_frame_count");
	char str[][50] = {"SmallFish","Croaker","AngelFish","Amphiprion","PufferS","Bream","Porgy","Chelonian","Lantern","Ray","Shark","GoldenTrout","GShark","GMarlinsFish","GrouperFish","JadePerch","MarlinsFish","PufferB"};

	for(int i = k_Fish_Type_SmallFish; i<k_Fish_Type_Count; i++)
	{
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
	}

	PersonalAudioEngine::sharedEngine();


	CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
	textureCache->addImage(STATIC_DATA_STRING("button_add"));
	textureCache->addImage(STATIC_DATA_STRING("button_sub"));

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("menulayer_plist"));

	//textureCache->addImage(STATIC_DATA_STRING("button_pause_normal"));//�����ҵ���ͣ��ť�ˣ��Ƿ��ھ���֡���
	//textureCache->addImage(STATIC_DATA_STRING("button_pause_selected"));
	textureCache->addImage(STATIC_DATA_STRING("button_music_normal"));
	textureCache->addImage(STATIC_DATA_STRING("button_music_selected"));
	textureCache->addImage(STATIC_DATA_STRING("button_photo_normal"));
	textureCache->addImage(STATIC_DATA_STRING("button_photo_selected"));
	textureCache->addImage(STATIC_DATA_STRING("button_fish_normal"));
	textureCache->addImage(STATIC_DATA_STRING("button_fish_selected"));


	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("cannon_plist"));
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("bullet_plist"));
}


void GameScene::pauseAndContinue()
{
	if(_nowRunStatus == k_Operate_Resume)
	{
		operateAllSchedulerAndActions(this,k_Operate_Pause);
		_nowRunStatus = k_Operate_Pause;
		_touchLayer->setTouchEnabled(false);
		addChild(_menuLayer);////////////////////////////////////////���
	}
	else if(_nowRunStatus == k_Operate_Pause)
	{
		operateAllSchedulerAndActions(this,k_Operate_Resume);
		_nowRunStatus = k_Operate_Resume;
		_touchLayer->setTouchEnabled(true);
		_paneLayer->setMenuResume();
		this->removeChildByTag(MENU_LAYER_TAG);
		//removeChild(_menuLayer);�ۿ������ŷ��������������ԭ��û������������tag����
	}
}

void GameScene::operateAllSchedulerAndActions( cocos2d::CCNode* node, OperateFlag flag )
{
	if(node->isRunning()){
		if(flag == k_Operate_Pause)
			node->pauseSchedulerAndActions();  
		else if(flag == k_Operate_Resume)
			node->resumeSchedulerAndActions();

		CCArray* tt = node->getChildren();  
		if(tt != NULL && tt->count()>0){
			CCObject* iterator;
			CCARRAY_FOREACH(tt, iterator){
				CCNode* child = (CCNode*)iterator;
				this->operateAllSchedulerAndActions(child, flag);
			}  
		}  
	}
}

void GameScene::cannonAimAt( CCPoint target )
{
	_cannonLayer->aimAt(target);
}

void GameScene::cannonShootTo( CCPoint target )
{
	int cost = _cannonLayer->getWeapon()->getCannonValue()->getCannonCost();
	int currentGold = FishingJoyData::shareFishingJoyData()->getGold();
	if(currentGold >= cost && target.y >= 100)
	{
		if(-cost < 0)
		{
			alterGold(-cost);
		}
		_cannonLayer->shootTo(target);
	}
	
}

bool GameScene::checkOutCollisionBetweenFishesAndBullet( Bullet *bullet )
{
	Weapon* weapon = _cannonLayer->getWeapon();
	CCPoint bulletPoint = bullet->getCollisionPoint();
	CCArray* fishArray = _fishLayer->getFishes();
	CCObject* iterator;
	CCARRAY_FOREACH(fishArray,iterator)
	{
		Fish* fish = (Fish*)iterator;
		if(fish != NULL && fish->isRunning() && !fish->getIsCaught())
		{
			if(PHYSICS_WORLD_IS_CONTACT(fish->getFishSprite(), bullet->getBulletSprite()))
			{
				//CCLog("%lf   %lf", fish->getFishSprite()->getTextureRect().size.width, fish->getFishSprite()->getTextureRect().size.height);
				//CCLog("%lf   %lf", bullet->getBulletSprite()->getTextureRect().size.width, bullet->getBulletSprite()->getTextureRect().size.height);
				//CCLog("fish bullet");
				fishWillBeCaught(fish,bullet);
				bullet->end();
				return true;
			}
			//CCLog("%lf %lf %lf %lf %lf %lf",fish->getCollisionArea().origin.x,fish->getCollisionArea().origin.y,fish->getCollisionArea().size.width,fish->getCollisionArea().size.height,bulletPoint.x,bulletPoint.y);
			/*if(fish->getCollisionArea().containsPoint(bulletPoint))
			{
				bullet->end();
				return true;
			}*/
		}
	}
	return false;
}

void GameScene::checkOutCollisionBetweenFishesAndFishingNet( Bullet *bullet )
{
	Weapon *weapon = _cannonLayer->getWeapon();
	CCRect fishNetRect = weapon-> getCollisionArea(bullet);
	CCArray *fishSet = _fishLayer->getFishes();
	CCObject *iterator;
	FishNet *fishNet = (FishNet *)bullet->getUserObject();
	CCARRAY_FOREACH(fishSet, iterator)
	{
		Fish *fish = (Fish *)iterator;

		/************************************************************************/
		/* 
		��ʼû���ж�fish->getIsCaught()�������������������ʧ���ȵ�������ʧ��ų��ֿ�ʼ����
		ԭ��������box����������һֱ�ж��������ײ������ÿ֡����ִ��fish��caught�ĺ��������������
		��һ�о���stopallaciton��������Ҫ��������ʧ�ˣ��ż���������ײ��û��stopallaction����Ķ����Ż�ִ����ȥ
		������û�뵽���������һֱ������Ϊʲô��ʧ��ԭ��
		*/
		/************************************************************************/
		if(!fish->getIsCaught() && PHYSICS_WORLD_IS_CONTACT(fish->getFishSprite(), fishNet->getFishNetSprite()))
		{
			//CCLog("fish fishNetbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");

			fishWillBeCaught(fish, bullet);
		}
		//if(!fish->getIsCaught() && fishNetRect.intersectsRect(fish->getCollisionArea()) && fishNet->isVisible())
		//{
		//	fishWillBeCaught(fish);
		//	//CCRect tt = fish->getCollisionArea();
		//	//CCLog("%lf %lf %lf %lf ",fishNetRect.origin.x, fishNetRect.origin.y, fishNetRect.size.width,fishNetRect.size.height);
		//	//CCLog("%lf %lf %lf %lf \n\n",tt.origin.x, tt.origin.y, tt.size.width,tt.size.height);
		//}
	}
}


void GameScene::checkOutCollision()
{
	CCArray* bulletArray = _cannonLayer->getWeapon()->getBullets();
	CCObject* iterator;
	CCARRAY_FOREACH(bulletArray,iterator)
	{
		Bullet* bullet = (Bullet*)iterator;
		if(bullet != NULL && bullet->isVisible())
		{
			CCPoint bPosition = bullet->getParent()->convertToWorldSpace(bullet->getPosition());
			if(bPosition.y > 100 && checkOutCollisionBetweenFishesAndBullet(bullet))
			{
				//checkOutCollisionBetweenFishesAndFishingNet(bullet);
			}
		}
		//��ײ��һ֡net��body��û��������������Ҫ��������.��fishNet�н������������һ֡�����ײ
		FishNet *fishNet = (FishNet *)bullet->getUserObject();
		if(fishNet != NULL && fishNet->isVisible())
			checkOutCollisionBetweenFishesAndFishingNet(bullet);
	}
}

void GameScene::update( float delta )
{
	PHYSICS_WORLD_TICK(delta);
	checkOutCollision();
}

void GameScene::fishWillBeCaught( Fish* fish , Bullet* bullet)
{
	//��ȡ���ڵİٷֱȣ�ͨ�����ε�static��һ�α�׼�����ڶ��ξ�����ֵ
	//��ȡ��İٷֱȣ�����ͬ��
	//������ˣ�ȡһ��������ȴ�С���ܷ񲶻�

	float t = fish->getFishPro() * bullet->getBulletPro();
	float now = CCRANDOM_0_1();
	int doubleGold = 1;
	if(_type == 3 || _type == 4)
		doubleGold = 2;
	if(t >= now)
	{
		PersonalAudioEngine::sharedEngine()->playEffect(kEffectCoins);
		
		int cost = fish->getFishGold() * doubleGold;
		if(cost > 0)
		{
		CCPoint tt = fish->getParent()->convertToWorldSpace(fish->getPosition());
		_goldShowLayer->showGold(tt, cost);
		alterGold(cost);
		}
		fish->beCaught();
	}
}

void GameScene::alterGold( int delta )
{
	FishingJoyData::shareFishingJoyData()->alterGold(delta);
	FishingJoyData::shareFishingJoyData()->flush();
	int goldNum = FishingJoyData::shareFishingJoyData()->getGold();
	_paneLayer->getGoldCounterLayer()->setNumber(goldNum);
}


void GameScene::onEnterTransitionDidFinish()
{
	CCScene::onEnterTransitionDidFinish();
	PersonalAudioEngine::sharedEngine()->playBackgroundMusic(_type + 1);
}

void GameScene::scheduleTimeUp()
{
	this->alterGold(STATIC_DATA_INT("recovery_gold"));
	//this->alterGold(50);
}

void GameScene::showCountDown(int i)
{
	CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
	CCString *tt = CCString::createWithFormat(STATIC_DATA_STRING("count_down_three"), i + 1);
	CCSprite *sp = CCSprite::createWithTexture(textureCache->textureForKey(tt->getCString()));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	sp->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
	sp->setScale(0.0f);
	addChild(sp);
	sp->runAction(CCSequence::create(CCDelayTime::create(i), CCScaleTo::create(1.0f,1.0f), CCCallFuncO::create(this,callfuncO_selector(GameScene::showCountDownCallback),(CCObject*)sp) ,NULL));
}

void GameScene::showCountDownCallback( CCObject *sender )
{
	CCSprite *sp = (CCSprite *)sender;
	removeChild(sp);
}

void GameScene::goldBoxAction()
{
	_goldShowLayer->goldBoxAction();
}
