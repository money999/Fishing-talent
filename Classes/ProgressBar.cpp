#include "ProgressBar.h"

ProgressBar::ProgressBar()
{

}

ProgressBar::~ProgressBar()
{

}

ProgressBar* ProgressBar::create( ProgressDelegate* target, CCSprite *sprite )
{
	ProgressBar *tt = new ProgressBar();
	tt->autorelease();
	tt->init(target,sprite);
	return tt;
}

bool ProgressBar::init( ProgressDelegate* target, CCSprite *sprite )
{
	CCProgressTimer::initWithSprite(sprite);
	_target = target;
	setType(kCCProgressTimerTypeBar);
	setMidpoint(ccp(0,0.5));
	setSpeed(1.0f);
	setBarChangeRate(ccp(1,0));
	return true;
}

void ProgressBar::progressBy( float delta )
{
	_nextPercentage = delta + this->getPercentage();
	//CCLog("%lf", _nextPercentage);
	bool finishTmp = false;
	if(_nextPercentage >= 46)
	{
		finishTmp = true;
	}
	
	stopActionByTag(k_Progress_Action);

	CCArray *actions = CCArray::createWithCapacity(2);
	float duration = delta/getSpeed();
	CCProgressTo *progressTo = CCProgressTo::create(duration, _nextPercentage);
	actions->addObject(progressTo);
	if (finishTmp)
	{
		CCCallFunc *callFunc1 = CCCallFunc::create(this, callfunc_selector(ProgressBar::loadingFinished));
		actions->addObject(callFunc1);
	}
	CCSequence *seq = CCSequence::create(actions);
	CCCallFunc *callFunc2 = CCCallFunc::create(this, callfunc_selector(ProgressBar::updatePercentage));
	//allFunc2->setDuration(duration);
	CCSpawn * spawn = CCSpawn::createWithTwoActions(seq, callFunc2);
	spawn->setTag(k_Progress_Action);
	setPercentage(_nextPercentage);
	runAction(spawn);
}


void ProgressBar::progressByAnim( float delta )
{
	_nextPercentage = delta + this->getPercentage();
	if(_nextPercentage <= 100)
	{
		setPercentage(_nextPercentage);
		this->updatePercentage();
	}
}


void ProgressBar::setBackground( CCNode* bg )
{
	if(_background == bg)
		return ;
	removeChild(_background,true);
	_background = bg;
	CCSize size = this->getSprite()->getContentSize();
	_background->setPosition(ccp(size.width * 0.5, size.height * 0.5));
	this->addChild(_background, -1);
}

void ProgressBar::setForeground( CCNode* fg )
{
	if(_foreground == fg)
		return ;
	removeChild(_foreground,true);
	_foreground = fg;
	CCSize size = this->getSprite()->getContentSize();
	_foreground->setPosition(ccp(size.width * 0.5, size.height * 0.5));
	this->addChild(_foreground, 1);
}

void ProgressBar::loadingFinished()
{
	if(_target!=NULL)
	{
		_target->loadingFinished();
	}
}

void ProgressBar::updatePercentage()
{
	if(_target!=NULL)
	{
		_target->progressPercentageSetter(_nextPercentage);
	}
}
