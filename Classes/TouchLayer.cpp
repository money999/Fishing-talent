#include "TouchLayer.h"
#include "GameScene.h"

TouchLayer::TouchLayer()
{
	_isRun = true;
}

TouchLayer::~TouchLayer()
{

}

bool TouchLayer::init()
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		setTouchEnabled(_isRun);//默认自动开启
		return true;
	} while (0);
	return false;
}

void TouchLayer::setTouchEnabled( bool value )
{
	CCLayer::setTouchEnabled(value);
}

void TouchLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool TouchLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	
	//const CCPoint& uiPoint = pTouch->getLocation();
	//CCDirector::sharedDirector()->convertToGL(uiPoint);
	((GameScene*)this->getParent())->cannonAimAt(pTouch->getLocation());//location就是GL的坐标

	return true;//true表示会继续下面的ended的事件，false就不会了
}

void TouchLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	((GameScene*)this->getParent())->cannonAimAt(pTouch->getLocation());
}

void TouchLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	((GameScene*)this->getParent())->cannonShootTo(pTouch->getLocation());
}

CCPoint TouchLayer::locationFromTouch( CCTouch *pTouch )
{
	return CCDirector::sharedDirector()->convertToGL(pTouch->getLocation());//不要转成GL了，转了导致炮台在左右边界时旋转错误，左上角时是水平角度，左下角时变成有一定的角度，相反了
}


