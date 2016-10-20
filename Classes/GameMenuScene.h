#pragma once

#include "cocos2d.h"
#include "GameMenuLayer.h"
#include "PopupLayer.h"
//#include "platform/third_party/win32/iconv/iconv.h"
//#include "platform/third_party/win32/libraries/libiconv.lib"

USING_NS_CC;

class GameMenuScene : public CCScene
{
public:
	GameMenuScene();
	~GameMenuScene();
	virtual bool init();

	void buttonCallBack(CCObject* pSender);
	void addPopup();

	CREATE_FUNC(GameMenuScene);
protected:
	GameMenuLayer *_menuLayer;
	PopupLayer *_popupLayer;
private:

};