#include "WhereScene.h"
#include "GameMenuLayer.h"

WhereScene::WhereScene()
{

}

WhereScene::~WhereScene()
{

}

bool WhereScene::init()
{
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		PersonalAudioEngine::sharedEngine()->playBackgroundMusic(6);
		/*_backgroudLayer = BackgroundLayer::create(STATIC_DATA_STRING("game_menu_background"));
		CC_BREAK_IF(!_backgroudLayer);
		addChild(_backgroudLayer);*/
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite * sp = CCSprite::create(STATIC_DATA_STRING("game_menu_background"));
		sp->setPosition(ccp(winSize.width/2, winSize.height/2));
		CCActionInterval * ripple3D = CCLiquid::create(99, CCSize(160, 120), 50, 2.0f);
		sp->runAction(ripple3D);
		addChild(sp);

		CCNode *node = SceneReader::sharedSceneReader()->createNodeWithSceneFile("whereScenejson.json");
		addChild(node);

		scrollView = ScrollLayer::create();
		this->addChild(scrollView);
		startButton();
		backButton();
		return true;
	} while (0);
	return false;
}

void WhereScene::startButton()
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	CCString *str;
	CCSprite *ttt;
	str = CCString::createWithFormat(STATIC_DATA_STRING("ui_2p_006_go_cn"),1);
	ttt = CCSprite::create(str->getCString());

	CCScale9Sprite * c91=CCScale9Sprite::create(str->getCString());
	CCControlButton * mybutton1=CCControlButton::create(c91);

	mybutton1->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.10));
	mybutton1->setTouchPriority(-1);//////////////////一定要改啊！后面layer的是0。差点就放弃button了
	mybutton1->setAdjustBackgroundImage(true);
	mybutton1->setPreferredSize(ttt->getContentSize());
	ttt->release();

	//mybutton1->setBackgroundSpriteForState(c92,CCControlStateHighlighted);

	mybutton1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(WhereScene::startDown),
		CCControlEventTouchDown
		);

	mybutton1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(WhereScene::startUpInside),
		CCControlEventTouchUpInside
		);
	mybutton1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(WhereScene::startUpOutside),
		CCControlEventTouchUpOutside
		);
	/*mybutton1->runAction(CCRepeatForever::create(CCSequence::create( CCShaky3D::create(1.0,CCSize(1,5),10,false),CCStopGrid::create(),CCDelayTime::create(1.0f),NULL)));
	this->addChild(mybutton1);*/
	_startButton = CCNode::create();
	_startButton->addChild(mybutton1);
	CCFiniteTimeAction *seq = CCRepeatForever::create(CCSequence::create( CCShaky3D::create(0.5,CCSize(1,5),10,false),CCStopGrid::create(),CCDelayTime::create(1.0f),NULL));
	seq->setTag(k_start_button_action);
	_startButton->runAction(seq);
	this->addChild(_startButton);
}

void WhereScene::startDown(CCObject * sender,CCControlEvent){
	_startButton->stopActionByTag(k_start_button_action);
}

void WhereScene::startUpInside(CCObject * sender,CCControlEvent){
	int type = scrollView->getNowCur();

	CCTransitionScene * reScene = NULL;
	CCScene *temp = LoadingLayer::scene(type + 1);
	float t = 1.2f;
	reScene = CCTransitionCrossFade::create(t, temp);
	//CCDirector::sharedDirector()->replaceScene(reScene);
	CCDirector::sharedDirector()->replaceScene(temp);
}

void WhereScene::startUpOutside(CCObject * sender,CCControlEvent){
	CCFiniteTimeAction *seq = CCRepeatForever::create(CCSequence::create( CCShaky3D::create(0.5, CCSize(1,5), 10, false),CCStopGrid::create(),CCDelayTime::create(1.0f),NULL));
	seq->setTag(k_start_button_action);
	_startButton->runAction(seq);
}


void WhereScene::backButton()
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	CCString *str;
	CCSprite *ttt;
	str = CCString::createWithFormat(STATIC_DATA_STRING("botton_defray_back"),1);
	ttt = CCSprite::create(str->getCString());
	CCScale9Sprite *nor=CCScale9Sprite::create(str->getCString());

	str = CCString::createWithFormat(STATIC_DATA_STRING("botton_defray_back"),2);
	CCScale9Sprite *sel=CCScale9Sprite::create(str->getCString());

	CCControlButton * mybutton1=CCControlButton::create(nor);

	//mybutton1->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.8));
	mybutton1->setTouchPriority(-1);
	mybutton1->setAdjustBackgroundImage(true);
	mybutton1->setPreferredSize(ttt->getContentSize());
	ttt->release();

	mybutton1->setBackgroundSpriteForState(sel,CCControlStateHighlighted);

	mybutton1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(WhereScene::backDown),
		CCControlEventTouchDown
		);

	mybutton1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(WhereScene::backUpInside),
		CCControlEventTouchUpInside
		);
	mybutton1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(WhereScene::backUpOutside),
		CCControlEventTouchUpOutside
		);

	_backButton = CCNode::create();
	_backButton->addChild(mybutton1);
	_backButton->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.90));
	_backPoint = _backButton->getPosition();
	CCPoint endPoint = ccpAdd(_backPoint, ccp(-39,0));
	CCFiniteTimeAction *seq = CCRepeatForever::create(CCSequence::create(CCEaseBounceOut::create(CCMoveTo::create(1.0,endPoint)), CCMoveTo::create(0.5, _backPoint) ,CCDelayTime::create(0.5),NULL));
	seq->setTag(k_back_button_action);
	_backButton->runAction(seq);
	this->addChild(_backButton);
}

void WhereScene::backDown( CCObject * sender,CCControlEvent )
{
	_backButton->stopActionByTag(k_back_button_action);
	_backButton->stopActionByTag(k_back_button_action_up);
}

void WhereScene::backUpInside( CCObject * sender,CCControlEvent )
{
	CCTransitionScene * reScene = NULL;
	CCScene *temp = GameMenuLayer::scene();
	float t = 1.2f;
	reScene = CCTransitionProgressRadialCCW::create(t, temp);
	CCDirector::sharedDirector()->replaceScene(reScene);
	//CCDirector::sharedDirector()->replaceScene(temp);
}


void WhereScene::backUpOutside( CCObject * sender,CCControlEvent )
{
	CCFiniteTimeAction *seq = CCSequence::create(CCMoveTo::create(0.5,_backPoint),CCDelayTime::create(0.5), CCCallFunc::create(this, callfunc_selector(WhereScene::backCall)),NULL);
	seq->setTag(k_back_button_action_up);
	_backButton->runAction(seq);
}

void WhereScene::backCall()
{
	CCPoint endPoint = ccpAdd(_backPoint, ccp(-39,0));
	CCFiniteTimeAction *seq = CCRepeatForever::create(CCSequence::create(CCEaseBounceOut::create(CCMoveTo::create(1.0,endPoint)), CCMoveTo::create(0.5, _backPoint) ,CCDelayTime::create(0.5),NULL));
	seq->setTag(k_back_button_action);
	_backButton->runAction(seq);
}


