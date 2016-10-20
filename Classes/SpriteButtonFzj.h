#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;
using namespace std;

class SpriteButtonFzj : public CCSprite
{
	CC_SYNTHESIZE_READONLY(CCSprite*,_normalBKSprite,NormalBKSprite);
	CC_SYNTHESIZE_READONLY(CCSprite*,_selectedBKSprite,SelectedBKSprite);
	CC_SYNTHESIZE_READONLY(CCSprite*,_normalTextSprite,NormalTextSprite);
	CC_SYNTHESIZE_READONLY(CCSprite*,_selectedTextSprite,SelectedTextSprite);
public:
	SpriteButtonFzj();
	~SpriteButtonFzj();
	bool setImage(string normalBK, string selectedBK, string normalText, string selectedText);
	void setOffset(float normalX, float normalY, float selectX,float selectY);
	virtual bool init();
	CREATE_FUNC(SpriteButtonFzj);
protected:

};