#pragma once

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "ScrollLayer.h"
#include "cocos-ext.h"
#include "SpriteButtonFzj.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GameMenuLayer;
enum{
	k_back_button_action = 0,
	k_back_button_action_up,
	k_start_button_action
};

class WhereScene : public CCScene
{

public:
	WhereScene();
	~WhereScene();

	void backButton();
	void backDown(CCObject * sender,CCControlEvent);
	void backUpInside(CCObject * sender,CCControlEvent);
	void backUpOutside(CCObject * sender,CCControlEvent);
	void backCall();

	void startButton();
	void startDown(CCObject * sender,CCControlEvent);
	void startUpInside(CCObject * sender,CCControlEvent);
	void startUpOutside(CCObject * sender,CCControlEvent);
	//void startUpOutside(CCObject * sender,CCControlEvent);



	virtual bool init();
	CREATE_FUNC(WhereScene);

protected:
	BackgroundLayer *_backgroudLayer;
	ScrollLayer *scrollView;

	CCNode *_startButton, *_backButton;
	CCPoint _backPoint;

private:

};