#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "ContactListener.h"
#include "StaticData.h"

#include "GLES-Render.h"

#define PTM_RATIO 32.0f

USING_NS_CC;

enum{
	p_bullet = 9,
	p_fishnet,
	p_fish
};

class PhySicsWorldFzj : public CCObject
{
	CC_SYNTHESIZE_READONLY(b2World*,_world,World);
	CC_SYNTHESIZE_READONLY(MyContactListener, *_contactListener, Contact);
public:
	PhySicsWorldFzj();
	~PhySicsWorldFzj();

	static PhySicsWorldFzj* sharedPhySicsWorldFzj();
	static void purge();
	static void destroyWorld();

	bool init();
	void addBoxBodyForSprite(CCSprite *sprite);
	void addBoxBodyForSprite(CCSprite *sprite, CCSize textureSize);
	void spriteDone(CCObject* sender);
	bool isContact(CCSprite *spriteA, CCSprite *spriteB);
	

	
	void tick(float dt);
	//CREATE_FUNC(PhySicsWorldFzj);

protected:
	GLESDebugDraw *_debugDraw;
	
private:

};

#define PHYSICS_WORLD_ADD_BODY_FOR_SPRITE(key) PhySicsWorldFzj::sharedPhySicsWorldFzj()->addBoxBodyForSprite( key )
#define PHYSICS_WORLD_ADD_BODY_FOR_SPRITE_CONTENT(key1,key2) PhySicsWorldFzj::sharedPhySicsWorldFzj()->addBoxBodyForSprite( key1, key2 )
#define PHYSICS_WORLD_IS_CONTACT(key1,key2) PhySicsWorldFzj::sharedPhySicsWorldFzj()->isContact(key1, key2)
#define PHYSICS_WORLD_SPRITE_DOWN(key) PhySicsWorldFzj::sharedPhySicsWorldFzj()->spriteDone(key)
#define PHYSICS_WORLD_TICK(key) PhySicsWorldFzj::sharedPhySicsWorldFzj()->tick(key)