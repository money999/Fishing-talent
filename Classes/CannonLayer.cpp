#include "CannonLayer.h"

CannonLayer::CannonLayer()
{

}

CannonLayer::~CannonLayer()
{

}

bool CannonLayer::init()
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		//_weapon->setPosition()
		CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
		CCSprite* UpSprite = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("button_add")));
		CCSprite* DownSprite = CCSprite::createWithTexture(textureCache->textureForKey(STATIC_DATA_STRING("button_sub")));
		_addItem = CCMenuItemSprite::create(UpSprite,UpSprite,this,menu_selector(CannonLayer::switchCannon));
		_subItem = CCMenuItemSprite::create(DownSprite,DownSprite,this,menu_selector(CannonLayer::switchCannon));
		
		CCMenu *menu = CCMenu::create(_subItem, _addItem, NULL);
		menu->alignItemsHorizontallyWithPadding(87);
		menu->setPosition(ccp(size.width * 0.497, 35));//danteng
		this->addChild(menu);

		_weapon = Weapon::create();
		addChild(_weapon);
		_weapon->setPosition(ccp(size.width * 0.495 ,20));
		return true;
	} while (0);
	return false;
}

void CannonLayer::switchCannon( CCObject *sender )
{
	CannonType type = _weapon->getCannonValue()->getType();
	if((CCMenuItemSprite*)sender == _addItem)
	{
		_weapon->getCannonValue()->setType((CannonType)(type + 1));
		PersonalAudioEngine::sharedEngine()->playEffect(kEffectSwichCannonLeft);
	}
	else if((CCMenuItemSprite*)sender == _subItem)
	{
		_weapon->getCannonValue()->setType((CannonType)(type - 1));
		PersonalAudioEngine::sharedEngine()->playEffect(kEffectSwichCannonRight);
	}
}

void CannonLayer::aimAt( CCPoint target )
{
	_weapon->aimAt(target);
}

void CannonLayer::shootTo( CCPoint target )
{
	_weapon->shootTo(target);
}

Weapon* CannonLayer::getWeapon()
{
	return _weapon;
}
