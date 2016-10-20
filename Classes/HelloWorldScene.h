#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
#include "PhysicsWorldFzj.h"
#include "LoadingLayer.h"

#include "StaticData.h"
#include "GLES-Render.h"
#include "BezierFzj.h"

//#include "Box2D/Common/b2Draw.h"

USING_NS_CC;

class HelloWorld : public cocos2d::CCLayer
{

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);


	void printDebug(float dt);


	HelloWorld();
	~HelloWorld();


	
	void spawnCar();
	void spawnCat();
	void spriteDone(CCObject* sender);
	void secondUpdate(float dt);
	void cUpdate(float dt);


	/*void tick(float dt);
	void addBoxBodyForSprite(CCSprite *sprite)  ;*/

	virtual void draw();


private:
	CCSprite* r1;
	CCNode *n1;
	CCNode *n2;
	CCNode *n3;

	//b2World *_world;
	//MyContactListener *_contactListener; 

	//PhySicsWorldFzj *_world;

	CCSprite *car;
	CCSprite *cat;

	GLESDebugDraw *_debugDraw;

};

#endif // __HELLOWORLD_SCENE_H__
