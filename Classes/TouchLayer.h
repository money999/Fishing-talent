#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameScene;
class TouchLayer : public CCLayer
{
	CC_SYNTHESIZE(bool, _isRun, isRun);
public:
	TouchLayer();
	~TouchLayer();
	bool init();
	

	CCPoint locationFromTouch(CCTouch *pTouch);

	virtual void setTouchEnabled(bool value);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	CREATE_FUNC(TouchLayer);
protected:
private:

};