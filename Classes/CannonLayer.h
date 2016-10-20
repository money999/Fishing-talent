#pragma once
#include "cocos2d.h"
#include "Weapon.h"
#include "PersonalAudioEngine.h"
USING_NS_CC;

class CannonLayer : public CCLayer
{
public:
	CannonLayer();
	~CannonLayer();
	bool init();
	void switchCannon(CCObject *sender);
	void aimAt(CCPoint target);
	void shootTo (CCPoint target);
	Weapon* getWeapon();
	CREATE_FUNC(CannonLayer);
protected:
	Weapon* _weapon;
	CCMenuItemSprite* _addItem;
	CCMenuItemSprite* _subItem;
private:
};