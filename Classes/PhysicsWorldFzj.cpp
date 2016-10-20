#include "PhysicsWorldFzj.h"

static PhySicsWorldFzj *g_sharedPhySicsWorldFzj = NULL;

PhySicsWorldFzj* PhySicsWorldFzj::sharedPhySicsWorldFzj()
{
	if(g_sharedPhySicsWorldFzj == NULL)
	{
		g_sharedPhySicsWorldFzj = new PhySicsWorldFzj();
		g_sharedPhySicsWorldFzj->init();

	}
	return g_sharedPhySicsWorldFzj;
}


void PhySicsWorldFzj::purge()
{
	CC_SAFE_RELEASE_NULL(g_sharedPhySicsWorldFzj);
}

void PhySicsWorldFzj::destroyWorld()
{
	CC_SAFE_DELETE(g_sharedPhySicsWorldFzj);
}


PhySicsWorldFzj::PhySicsWorldFzj()
{

}

PhySicsWorldFzj::~PhySicsWorldFzj()
{
	CC_SAFE_DELETE(_debugDraw);
	CC_SAFE_DELETE(_contactListener);
	CC_SAFE_DELETE(_world);
}



bool PhySicsWorldFzj::init()
{
	do 
	{
		_world = new b2World(b2Vec2(0.0f,0.0f));
		_world->SetAllowSleeping(false);
		_contactListener = new MyContactListener();
		_world->SetContactListener(_contactListener);

		_debugDraw =new GLESDebugDraw( PTM_RATIO );

		uint32 flags =0;
		//flags += b2DebugDraw::e_shapeBit;
		flags += 0x0001;
		_debugDraw->SetFlags(flags);
		_world->SetDebugDraw(_debugDraw);

		//this->schedule(schedule_selector(PhySicsWorldFzj::tick));
		/************************************************************************/
		/* 
		�����÷�����ԭ��physicsWorldFzj-p�� HelloWorldScene-h
		1����p����schedule����ʱ����tick���������h�����addchild��_world��������ײ����ʧЧ����Ϊ��retain���ԣ���ʵ���У�Ӧ����ͬ�������⿴2
		2����p�в�����schedule����tick����h��h���schedule����ʱ����tick������addchild��_world����������Ч���о�������ͬ����Ч��
		*/
		/************************************************************************/
		return true;
	} while (0);
	return false;
}


//�󶨾����û�����
void PhySicsWorldFzj::addBoxBodyForSprite( CCSprite *sprite )
{

	CCPoint spPoint = sprite->getParent()->convertToWorldSpace(sprite->getPosition());/*��tmd�Ĺ���Ĺ��̰��������������ᶼҪ������ˣ����ڿ����cpp��ʱ�������ǰ�����
																					  һ���ע���ˣ�����ǿ��ġ����Ե��������F10����ʱ��ŷ��֣��Ұ�����ע���ˣ������Ǿ����
																					  ������ô���£�����Ȼ���еĲ����ҿ����Ĵ��룡����*/
	//CCPoint spPoint = sprite->getPosition();

	b2BodyDef *spriteBodyDef = new b2BodyDef();
	spriteBodyDef->type = b2_dynamicBody;  
	spriteBodyDef->position = b2Vec2((float)(spPoint.x / PTM_RATIO), (float)(spPoint.y / PTM_RATIO));
	spriteBodyDef->userData = sprite;  

	b2Body *spriteBody = _world->CreateBody(spriteBodyDef);  


	b2PolygonShape *spriteShape = new b2PolygonShape();  

	if(sprite->getTag() == p_bullet)
	{
		int *type = (int *)sprite->getUserData();
		int ty = *type + 1;
		CCString *tt = CCString::createWithFormat(STATIC_DATA_STRING("bullet_feature_num"), ty);
		int num = STATIC_DATA_INT(tt->getCString());
		b2Vec2 verts[10];
		for(int i = 1; i<= num; i++)
		{
			CCString *kk = CCString::createWithFormat(STATIC_DATA_STRING("bullet_feature_formate"), ty, i, "x");
			int x = STATIC_DATA_INT(kk->getCString());
			CCString *gg = CCString::createWithFormat(STATIC_DATA_STRING("bullet_feature_formate"), ty, i, "y");
			int y = STATIC_DATA_INT(gg->getCString());
			verts[i - 1] = b2Vec2(x/PTM_RATIO, y/PTM_RATIO);
		}
		spriteShape->Set(verts, num);
	}
	else
		spriteShape->SetAsBox((float)(sprite->getTextureRect().size.width / 2.0f / PTM_RATIO), (float)(sprite->getTextureRect().size.height / 2.0f / PTM_RATIO ));

	b2FixtureDef *spriteShapeDef = new b2FixtureDef();
	spriteShapeDef->shape = spriteShape;  
	spriteShapeDef->density = 10.0f;
	//spriteShapeDef->isSensor = true;
	spriteBody->CreateFixture(spriteShapeDef);
}

void PhySicsWorldFzj::addBoxBodyForSprite( CCSprite *sprite, CCSize textureSize )
{

	CCPoint spPoint = sprite->getParent()->convertToWorldSpace(sprite->getPosition());

	//CCPoint spPoint = sprite->getPosition();

	b2BodyDef *spriteBodyDef = new b2BodyDef();
	spriteBodyDef->type = b2_dynamicBody;  
	spriteBodyDef->position = b2Vec2((float)(spPoint.x / PTM_RATIO), (float)(spPoint.y / PTM_RATIO));
	spriteBodyDef->userData = sprite;  
	b2Body *spriteBody = _world->CreateBody(spriteBodyDef);  


	b2PolygonShape *spriteShape = new b2PolygonShape();  

	if(sprite->getTag() == p_fish)
	{
		/*int num = 4;
		b2Vec2 verts[] = {///�õ�����ʱ�룡
			b2Vec2((float)(0.0f/PTM_RATIO), (float)(52.0f/PTM_RATIO)),
			b2Vec2((float)(-52.0f/PTM_RATIO), (float)(0.0f/PTM_RATIO)),
			b2Vec2((float)(0.0f/PTM_RATIO), (float)(-52.0f/PTM_RATIO)),
			b2Vec2((float)(52.0f/PTM_RATIO), (float)(0.0f/PTM_RATIO)),
		};  */
		char *str = (char *)sprite->getUserData();
		CCString *tt = CCString::createWithFormat(STATIC_DATA_STRING("fish_feature_num"), str);
		int num = STATIC_DATA_INT(tt->getCString());
		b2Vec2 verts[20];
		for(int i = 1; i<= num; i++)
		{
			CCString *kk = CCString::createWithFormat(STATIC_DATA_STRING("fish_feature_formate"), str, i, "x");
			int x = STATIC_DATA_INT(kk->getCString());
			CCString *gg = CCString::createWithFormat(STATIC_DATA_STRING("fish_feature_formate"), str, i, "y");
			int y = STATIC_DATA_INT(gg->getCString());
			verts[i - 1] = b2Vec2(x/PTM_RATIO, y/PTM_RATIO);
		}
		spriteShape->Set(verts, num);
	}
	else
		spriteShape->SetAsBox((float)(textureSize.width / 2 / PTM_RATIO), (float)(textureSize.height / 2 / PTM_RATIO ));

		float tt = sprite->getContentSize().width;

	b2FixtureDef *spriteShapeDef = new b2FixtureDef();  
	spriteShapeDef->shape = spriteShape;  
	spriteShapeDef->density = 10.0f;  
	//spriteShapeDef->isSensor = true;  
	spriteBody->CreateFixture(spriteShapeDef);
}

//��������ľ������������������body��֮ɾ��
void PhySicsWorldFzj::spriteDone( CCObject* sender )
{

	CCSprite *sprite = (CCSprite *)sender;  

	b2Body* node = _world->GetBodyList();
	while(node)
	{
		b2Body* b=node;
		node = node->GetNext();
		CCSprite *curSprite = (CCSprite *)b->GetUserData();
		if(sprite == curSprite)
			_world->DestroyBody(b);
	}


	/*CCSprite *sprite = (CCSprite *)sender;  

	b2Body *spriteBody = NULL;  
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
}


//����������������
void PhySicsWorldFzj::tick( float dt )
{
	_world->Step(dt, 10, 10);  
	for (b2Body *b = _world->GetBodyList(); b != NULL; b = b->GetNext())  
	{  
		if (b->GetUserData() != NULL)
		{  
			CCSprite *sprite = (CCSprite*)b->GetUserData();
			CCPoint spPoint = sprite->getParent()->convertToWorldSpace(sprite->getPosition());
			b2Vec2 position;
			position.Set((float)(spPoint.x / PTM_RATIO), (float)(spPoint.y / PTM_RATIO));
			//float angle = CC_RADIANS_TO_DEGREES(sprite->getRotation());
			//float angle =   CC_RADIANS_TO_DEGREES(sprite->getRotation());
			float angle =-1 * CC_DEGREES_TO_RADIANS(sprite->getRotation());//�������õ��ǻ��ȣ���Ϊ�ǽǶȡ�����Ҳ���˹ؼ����һ�д����CC_RADIANS_TO_DEGREES��������֪��sprite->getRotation()�ǽǶȣ��ֲ�д���Ǵ����˺þã�
			b->SetTransform(position, angle);
		}
	}
}

//�����ײ
bool PhySicsWorldFzj::isContact( CCSprite *spriteA, CCSprite *spriteB )
{
	std::vector<MyContact>::iterator pos;
	for(pos = _contactListener->_contacts.begin();
		pos != _contactListener->_contacts.end(); ++pos) {
			MyContact contact =*pos;

			b2Body *bodyA = contact.fixtureA->GetBody();
			b2Body *bodyB = contact.fixtureB->GetBody();
			if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
				CCSprite *spriteAThis = (CCSprite *) bodyA->GetUserData();
				CCSprite *spriteBThis = (CCSprite *) bodyB->GetUserData();

				if (spriteA == spriteAThis && spriteB == spriteBThis) {
					return true;
				} else if (spriteB == spriteAThis && spriteA == spriteBThis) {
					return true;
				}
			}
	}
	return false;
}

