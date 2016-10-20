#pragma once

#include "cocos2d.h"
#include "ProgressDelegate.h"
#include "StaticData.h"
#include "ProgressBar.h"
#include "Fish.h"
#include "PersonalAudioEngine.h"
class GameScene;
USING_NS_CC;

class LoadingLayer : public CCLayer, public ProgressDelegate
{
public:
	LoadingLayer();
	~LoadingLayer();
	virtual bool init(int type);
	void initProgressBar();
	void cacheInit();
	void loadAnim(float delta);
	void loadAnimSub(int i);
	void launchGame(float delta);
	void loading(CCObject *sender);
	void loading1(CCObject *sender);
	void loading2(CCObject *sender);
	void loading3(CCObject *sender);
	//void (CCObject::*SEL_CallFuncO)(CCObject*);
	static CCScene* scene(int type);
	static LoadingLayer *create(int type);

	virtual void loadingFinished();
	virtual void progressPercentageSetter(float percentage);
	//CREATE_FUNC(LoadingLayer);
protected:

private:
	ProgressBar *_progressBar; 
	cocos2d::CCLabelTTF* _progressFg; 
	int _numSp;
	int _loadedSp;
	int animNum ;

	int _type;
};