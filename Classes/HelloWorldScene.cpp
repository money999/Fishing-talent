#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

	//layer->printDebug(0);
    // return the scene
    return scene;
}

HelloWorld::HelloWorld()
{

}


HelloWorld::~HelloWorld()
{
	//CC_SAFE_DELETE(_debugDraw);
	/*CC_SAFE_DELETE(_contactListener);*/
	//CC_SAFE_DELETE(_world);
	
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	for(int i=1; i<=5; i++)
	{
		const char * temp = STATIC_DATA_STRING(CCString::createWithFormat("fish_plist_%02d",i)->getCString());
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(temp);
	}
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("bullet_plist"));


	//_world = new b2World(b2Vec2(0.0f,0.0f));
	//_world->SetAllowSleeping(false);

	//_world = new PhySicsWorldFzj();
	//_world->init();


	//_debugDraw =new GLESDebugDraw( PTM_RATIO );

	//uint32 flags =0;
	////flags += b2DebugDraw::e_shapeBit;
	//flags += 0x0001;
	//_debugDraw->SetFlags(flags);

	//_world->getWorld()->SetDebugDraw(_debugDraw);

	//PhySicsWorldFzj::sharedPhySicsWorldFzj()->getWorld()->SetDebugDraw(_debugDraw);

	
	//CC_SAFE_RETAIN(_world);
	//addChild(_world);


	CCLabelTTF *title = CCLabelTTF::create("Collision", "Arial", 24);  
	title->setPosition(ccp(400, 400));
	addChild(title);

	spawnCar();  

	this->schedule(schedule_selector(HelloWorld::secondUpdate),1.0f);
	this->schedule(schedule_selector(HelloWorld::cUpdate));
	//this->schedule(schedule_selector(HelloWorld::tick));//每一帧都要调用，原来看博客传了1.0导致1秒更新一次物理世界的位置，当然就没有碰撞了……


	//_contactListener = new MyContactListener();
	//_world->SetContactListener(_contactListener);

	//layertt = LoadingLayer::create();
	//addChild(layertt);
	
    
    return true;
}


//cocos2d::CCPoint HelloWorld::getCon( CCPoint p1, CCPoint p2 , float hei)
//{
//	CCPoint midP = ccpMidpoint(p1, p2);
//	CCPoint vec1 = ccpSub(p1, p2);
//	float tx = vec1.x;
//	float ty = vec1.y;
//	vec1.x = -ty;
//	vec1.y = tx;
//	float dis = ccpDistance(vec1, ccp(0.0f,0.0f));
//	vec1.x = vec1.x/dis;
//	vec1.y = vec1.y/dis;
//	vec1.x = vec1.x * hei;
//	vec1.y = vec1.y * hei;
//	CCPoint ttt = ccpAdd(vec1,midP);
//	return ttt;
//}


void HelloWorld::spawnCar()
{
	CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
	
	CCString *frameSpriteName = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_format"),"GMarlinsFish",1);
	car= CCSprite::createWithSpriteFrameName(frameSpriteName->getCString());

	
	car->setTag(22);
	//car->setRotation(45);


	 car->setPosition(ccp(1280,400));  
	 CCActionInterval *bezierFzj = BezierFzj::createBezierFzj(6.0f, ccp(1280,400), ccp(0,400), -300, 300);

	//CCActionInterval* re = bezierForward->reverse();//反向操作竟然没有调用update函数！

	/*car->runAction(  
	bezierForward
	);*/
	car->runAction( 
		bezierFzj
		);


	/*car->runAction(CCRepeatForever::create(  
	CCSequence::create(  
	CCMoveTo::create(1.0f, ccp(-30, -50)),  
	CCMoveTo::create(1.0f, ccp(20, 20)),  
	CCMoveTo::create(1.0f, ccp(-50, 50)),
	NULL
	)));  */
	//addBoxBodyForSprite(car);
	//_world->addBoxBodyForSprite(car);


	//PHYSICS_WORLD_ADD_BODY_FOR_SPRITE(car);
	addChild(car); 
}

void HelloWorld::spawnCat()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();

	CCString* fileName = CCString::createWithFormat(STATIC_DATA_STRING("bullet_frame_format"),1);
	cat = CCSprite::createWithSpriteFrameName(fileName->getCString());


	float minY = cat->getContentSize().height / 2;  
	float maxY = winSize.height - cat->getContentSize().height / 2;  
	float rangeY = maxY - minY;  
	float acturalY = CCRANDOM_0_1() * rangeY;  
	float startX = winSize.width +cat->getContentSize().width / 2;  
	float endX = -cat->getContentSize().width / 2;  
	CCPoint startPos = ccp(startX, acturalY);
	CCPoint endPos = ccp(endX, acturalY);  


	cat->setPosition(startPos);
	cat->setTag(11);

	cat->runAction(CCSequence::create(CCMoveTo::create(1.0f, endPos),CCCallFuncO::create(this, callfuncO_selector(HelloWorld::spriteDone),(CCObject *)cat), NULL));  
	//addBoxBodyForSprite(cat);
	//_world->addBoxBodyForSprite(cat);
	//PHYSICS_WORLD_ADD_BODY_FOR_SPRITE(cat);
	addChild(cat);  
}

void HelloWorld::spriteDone( CCObject *sender )
{
	//_world->spriteDone(sender);
	//PHYSICS_WORLD_SPRITE_DOWN(sender);

	/*b2Body *spriteBody = NULL;
	for (b2Body *b = _world->GetBodyList(); b != NULL; b = b->GetNext())  
	{  
		if (b->GetUserData() != NULL)  
		{  
			CCSprite *curSprite = (CCSprite *)b->GetUserData();  
			if (sprite == curSprite)  
			{  
				spriteBody = b;  
			}  
		}  
	}  

	if (spriteBody != NULL)  
	{  
		_world->DestroyBody(spriteBody);
	}  */
	CCSprite *sprite = (CCSprite *)sender; 
	removeChild(sprite, true);  
}

void HelloWorld::secondUpdate( float dt )
{
	spawnCat();
}


void HelloWorld::cUpdate( float dt )
{
	//_world->tick(dt);
	//PHYSICS_WORLD_TICK(dt);
	//if(PHYSICS_WORLD_IS_CONTACT(car,cat))
	//if(_world->isContact(car,cat))
	//	CCLog("sdafadsfasfasdfadsf");
}


void HelloWorld::draw()
{
	CCLayer::draw();
	//_world->getWorld()->DrawDebugData();
	//PhySicsWorldFzj::sharedPhySicsWorldFzj()->getWorld()->DrawDebugData();
}


//void HelloWorld::tick( float dt )
//{
//	_world->Step(dt, 10, 10);  
//	for (b2Body *b = _world->GetBodyList(); b != NULL; b = b->GetNext())  
//	{  
//		if (b->GetUserData() != NULL)
//		{  
//			CCSprite *sprite = (CCSprite*)b->GetUserData();  
//
//			b2Vec2 position;
//			position.Set((float)(sprite->getPosition().x / PTM_RATIO), (float)(sprite->getPosition().y / PTM_RATIO));
//
//			float angle = CC_RADIANS_TO_DEGREES(sprite->getRotation());  
//			b->SetTransform(position, angle);
//		}
//	}
//
//
//
//
//	std::vector<b2Body *> toDestroy;
//	std::vector<MyContact>::iterator pos;
//	for(pos = _contactListener->_contacts.begin();
//		pos != _contactListener->_contacts.end(); ++pos) {
//			MyContact contact =*pos;
//
//			b2Body *bodyA = contact.fixtureA->GetBody();
//			b2Body *bodyB = contact.fixtureB->GetBody();
//			if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
//				CCSprite *spriteA = (CCSprite *) bodyA->GetUserData();
//				CCSprite *spriteB = (CCSprite *) bodyB->GetUserData();
//
//				if (spriteA->getTag() ==1&& spriteB->getTag() ==2) {
//					toDestroy.push_back(bodyA);
//				} else if (spriteA->getTag() == 2&& spriteB->getTag() == 1) {
//					toDestroy.push_back(bodyB);
//				}
//			}
//	}
//
//	std::vector<b2Body *>::iterator pos2;
//	for(pos2 = toDestroy.begin(); pos2 != toDestroy.end(); ++pos2) {
//		b2Body *body =*pos2;
//		if (body->GetUserData() != NULL) {
//			CCSprite *sprite = (CCSprite *) body->GetUserData();
//			//[_spriteSheet removeChild:sprite cleanup:YES];
//			removeChild(sprite,true);
//		}
//		_world->DestroyBody(body);
//	}
//
//	if (toDestroy.size() >0) {
//		//[[SimpleAudioEngine sharedEngine] playEffect:@"hahaha.caf"];
//
//		CCLog("rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr");
//	}
//}
//
//
//void HelloWorld::addBoxBodyForSprite( CCSprite *sprite )
//{
//	b2BodyDef *spriteBodyDef = new b2BodyDef();
//	spriteBodyDef->type = b2_dynamicBody;  
//	spriteBodyDef->position = b2Vec2((float)(sprite->getPosition().x / PTM_RATIO), (float)(sprite->getPosition().y / PTM_RATIO));
//	spriteBodyDef->userData = sprite;  
//	b2Body *spriteBody = _world->CreateBody(spriteBodyDef);  
//
//
//
//	b2PolygonShape *spriteShape = new b2PolygonShape();  
//
//	if(sprite->getTag() == 1)
//	{
//		int num = 4;
//		b2Vec2 verts[] = {///用的是逆时针！
//		b2Vec2((float)(0.0f/PTM_RATIO), (float)(52.0f/PTM_RATIO)),
//		b2Vec2((float)(-52.0f/PTM_RATIO), (float)(0.0f/PTM_RATIO)),
//		b2Vec2((float)(0.0f/PTM_RATIO), (float)(-52.0f/PTM_RATIO)),  
//		b2Vec2((float)(52.0f/PTM_RATIO), (float)(0.0f/PTM_RATIO)),
//		};  
//		spriteShape->Set(verts, num);
//	}
//	else
//		spriteShape->SetAsBox((float)(sprite->getContentSize().width / 2 / PTM_RATIO), (float)(sprite->getContentSize().height / 2 / PTM_RATIO ));  
//
//	b2FixtureDef *spriteShapeDef = new b2FixtureDef();  
//	spriteShapeDef->shape = spriteShape;  
//	spriteShapeDef->density = 10.0f;  
//	spriteShapeDef->isSensor = true;  
//	spriteBody->CreateFixture(spriteShapeDef);  
//}


















//void HelloWorld::menuCloseCallback(CCObject* pSender)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//#else
//    CCDirector::sharedDirector()->end();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//#endif
//}

void HelloWorld::printDebug(float dt)
{
	//CCPoint r1World = r1->getParent()->

	CCLog("%lf  %lf", r1->getPosition().x, r1->getPosition().y);

	CCLog("%lf  %lf", n1->getPosition().x, n1->getPosition().y);

	CCLog("%lf  %lf", n2->getPosition().x, n2->getPosition().y);

	CCLog("%lf  %lf", n3->getPosition().x, n3->getPosition().y);


	CCPoint r1World = r1->getParent()->convertToWorldSpace(r1->getPosition());
	CCPoint n1World = n1->getParent()->convertToWorldSpace(n1->getPosition());
	CCPoint n2World = n2->getParent()->convertToWorldSpace(n2->getPosition());
	CCPoint n3World = n3->getParent()->convertToWorldSpace(n3->getPosition());


	CCLog("%lf  %lf", r1World.x, r1World.y);

	CCLog("%lf  %lf", n1World.x, n1World.y);

	CCLog("%lf  %lf", n2World.x, n2World.y);

	CCLog("%lf  %lf", n3World.x, n3World.y);

	//CCLog("%lf  %lf", n1->getPosition().x, n1->getPosition().y);
}




// this->schedule(secondUpdate, 1.0f);  

	//r1 = CCSprite::create();////精灵被多个父容器嵌套包含的时候的世界坐标sp->getParent()->convertToWorldSpace(sp->getPosition())即可。因为sp->getPosition()是相对于父容器而言的
	//n1 = CCNode::create();
	//n2 = CCNode::create();
	//n3 = CCNode::create();
	//
	//n1->addChild(r1);
	//r1->setPosition(ccp(10,10));

	//n2->addChild(n1);
	////n1->setPosition(ccp(20.0f,20.0f));

	//n3->addChild(n2);
	//n2->setPosition(ccp(30.0f,30.0f));

	//this->addChild(n3);
	//n3->setPosition(ccp(40.0f,40.0f));

	//this->schedule(schedule_selector(HelloWorld::printDebug),3.0);
    
   /* CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);*/








