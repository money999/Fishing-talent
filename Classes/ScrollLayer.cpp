#include "ScrollLayer.h"
#define PAGENUM 4

ScrollLayer::ScrollLayer()
{
	_nowCur = 0;
	_beginPoint = CCPointZero;
	_offsetPoint = CCPointZero;
}

ScrollLayer::~ScrollLayer()
{

}

bool ScrollLayer::init()
{
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		_scrollView = CCScrollView::create(CCSize(winSize.width ,winSize.height ));
		CCLayer * layer = CCLayer::create();
		for(int i = 0;i<PAGENUM;i++)
		{
			CCNode *node = CCNode::create();
			CCString * string = CCString::createWithFormat(STATIC_DATA_STRING("UI_selectStage"),i+1);
			CCSprite * sprite1 = CCSprite::create(string->getCString());
			string = CCString::createWithFormat(STATIC_DATA_STRING("UI_selectStage_bg"),i+1);
			CCSprite * sprite2 = CCSprite::create(string->getCString());
			string = CCString::createWithFormat(STATIC_DATA_STRING("UI_selectStage_bg"), 0);
			CCSprite * sprite3 = CCSprite::create(string->getCString());

			node->addChild(sprite1);
			node->addChild(sprite3);
			node->addChild(sprite2);
			sprite2->setPosition(ccp(-90.0f,40.0f));
			sprite3->setPosition(ccp(-90.0f,40.0f));

			node->setPosition(ccpAdd(ccp(winSize.width/2,(winSize.height + 100)/2),ccp(winSize.width*i,0)));
			layer->addChild(node);
		}
		_scrollView->setContainer(layer);
		_scrollView->setContentSize(CCSize(winSize.width * PAGENUM , winSize.height ));
		_scrollView->setTouchEnabled(false);
		_scrollView->setContentOffset(CCPoint(0,0));
		this->setTouchEnabled(true);
		this->addChild(_scrollView);
		return true;
	}
	while(0);
	return false;
}

void ScrollLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool ScrollLayer::ccTouchBegan( CCTouch * touch,CCEvent * pEvent )
{
	this->_beginPoint = touch->getLocation();
	this->_offsetPoint = this->_scrollView->getContentOffset();
	return true;
}

void ScrollLayer::ccTouchMoved( CCTouch * touch,CCEvent * pEvent )
{
	CCPoint point = touch->getLocation();
	CCPoint direction = ccpSub(point,this->_beginPoint);
	CCPoint spriteDirection = CCPoint(direction.x+this->_offsetPoint.x,0);
	this->_scrollView->setContentOffset(spriteDirection);
}

void ScrollLayer::ccTouchEnded( CCTouch * touch,CCEvent * pEvent )
{
	CCPoint endPoint = touch->getLocation();
	float offset = endPoint.x-this->_beginPoint.x;//只关心向左还是向右的
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if(fabs(offset) < winSize.width * 0.2)//这里有空再调一下
	{
		this->adjustScrollView(0);
	}
	else
	{
		this->adjustScrollView(offset);
	}
}

void ScrollLayer::adjustScrollView( float offset )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	if (offset < 0)
		_nowCur ++;
	else if (offset > 0)
		_nowCur --;

	if (_nowCur < 0)
		_nowCur = 0;
	else if (_nowCur > PAGENUM - 1)
		_nowCur = PAGENUM - 1;

	CCPoint adjustPoint = ccp(-winSize.width * _nowCur , 0.0f);
	this->_scrollView->setContentOffsetInDuration(adjustPoint, 0.39f);
}
