#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "StaticData.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ScrollLayer : public CCLayer
{
	CC_SYNTHESIZE(int, _nowCur, NowCur);
public:
	ScrollLayer();
	~ScrollLayer();
	virtual bool init();
	CREATE_FUNC(ScrollLayer);


	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch * touch,CCEvent * pEvent);
	void ccTouchMoved(CCTouch * touch,CCEvent * pEvent);
	void ccTouchEnded(CCTouch * touch,CCEvent * pEvent);
	void  adjustScrollView(float offset);

protected:
	CCScrollView * _scrollView;
	CCPoint _beginPoint;
	CCPoint _offsetPoint;
private:

};