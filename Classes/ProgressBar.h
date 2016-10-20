#pragma once

#include "cocos2d.h"
#include "ProgressDelegate.h"
USING_NS_CC;

enum{
	k_Progress_Action = 0
};

class ProgressBar : public CCProgressTimer
{
	CC_SYNTHESIZE(float, _speed, Speed);
public:
	ProgressBar();
	~ProgressBar();
	static ProgressBar* ProgressBar::create(ProgressDelegate* target, CCSprite *sprite);
	bool ProgressBar::init(ProgressDelegate* target, CCSprite *sprite);
	void progressBy(float delta);
	void progressByAnim(float delta);
	void setBackground(CCNode* bg);
	void setForeground (CCNode* fg);

	void loadingFinished();
	void updatePercentage();
protected:
private:
	ProgressDelegate* _target;
	CCNode* _background;
	CCNode* _foreground;

	float _nextPercentage;
};