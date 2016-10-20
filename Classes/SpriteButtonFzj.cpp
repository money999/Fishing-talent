#include "SpriteButtonFzj.h"


SpriteButtonFzj::SpriteButtonFzj()
{
	
}

SpriteButtonFzj::~SpriteButtonFzj()
{

}

void SpriteButtonFzj::setOffset( float normalX, float normalY, float selectX,float selectY )
{
	
	_normalTextSprite->setPositionX(_normalBKSprite->getContentSize().width * normalX);
	_normalTextSprite->setPositionY(_normalBKSprite->getContentSize().height * normalY);

	_selectedTextSprite->setPositionX(_selectedBKSprite->getContentSize().width * selectX);
	_selectedTextSprite->setPositionY(_selectedBKSprite->getContentSize().height * selectY);
}

bool SpriteButtonFzj::init()
{
	do 
	{
		CC_BREAK_IF(!CCSprite::init());
		return true;
	} while (0);
	return false;
}

bool SpriteButtonFzj::setImage( string normalBK, string selectedBK, string normalText, string selectedText )
{
	do 
	{
		_normalBKSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING(normalBK));
		CC_BREAK_IF(!_normalBKSprite);
		_selectedBKSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING(selectedBK));
		CC_BREAK_IF(!_selectedBKSprite);
		_normalTextSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING(normalText));
		CC_BREAK_IF(!_normalTextSprite);
		_selectedTextSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING(selectedText));
		CC_BREAK_IF(!_normalTextSprite);

		_normalBKSprite->addChild(_normalTextSprite);
		_selectedBKSprite->addChild(_selectedTextSprite);

		setOffset(0.5,0.5,0.5,0.5);//Ä¬ÈÏ¾ÓÖĞ
		return true;
	} while (0);
	return false;
}
