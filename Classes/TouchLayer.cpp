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
		setTouchEnabled(_isRun);//Ĭ���Զ�����
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
	((GameScene*)this->getParent())->cannonAimAt(pTouch->getLocation());//location����GL������

	return true;//true��ʾ����������ended���¼���false�Ͳ�����
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
	return CCDirector::sharedDirector()->convertToGL(pTouch->getLocation());//��Ҫת��GL�ˣ�ת�˵�����̨�����ұ߽�ʱ��ת�������Ͻ�ʱ��ˮƽ�Ƕȣ����½�ʱ�����һ���ĽǶȣ��෴��
}


