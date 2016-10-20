#include "ContactListener.h"


MyContactListener::MyContactListener() : _contacts() {
}

MyContactListener::~MyContactListener() {
}

void MyContactListener::BeginContact(b2Contact* contact) {
	
	MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };

	b2Body *bodyA = contact->GetFixtureA()->GetBody();
	b2Body *bodyB = contact->GetFixtureB()->GetBody();
	if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
		CCSprite *spriteAThis = (CCSprite *) bodyA->GetUserData();
		CCSprite *spriteBThis = (CCSprite *) bodyB->GetUserData();
		/*if(spriteAThis->getTag() ==10 || spriteBThis->getTag() == 10)
			CCLog("\nlistener\n %d %d" ,spriteAThis->getTag(), spriteBThis->getTag());*/
		
		if(spriteAThis->getTag()!= spriteBThis->getTag()/* && (spriteAThis->getTag() == 11 || spriteBThis->getTag() == 11)*/)
		{
			
			//int t = spriteAThis->getTag();
			//int m = spriteBThis->getTag();
			//CCLog("%d %d",t,m);

			//b2Manifold *mainfold = new b2Manifold();
			//mainfold = contact->GetManifold();
			//float xt = mainfold->localPoint.x;
			//float yt = mainfold->localPoint.y;
			////mainfold->points[0]

			//b2Vec2 t1 = bodyA->GetPosition();
			//b2Vec2 t2 = bodyB->GetPosition();

			//b2Vec2 t11 = bodyA->GetWorldPoint(bodyA->GetPosition());
			//b2Vec2 t22 = bodyB->GetWorldPoint(bodyB->GetPosition());

			//b2WorldManifold * tm = new b2WorldManifold();
			//contact->GetWorldManifold(tm);
			//b2Vec2 t33 = tm->points[0];

			//CCPoint t44 = spriteAThis->getParent()->convertToWorldSpace(spriteAThis->getPosition());
			//CCPoint t55 = spriteBThis->getParent()->convertToWorldSpace(spriteBThis->getPosition());

			_contacts.push_back(myContact);
		}
			
	}
}

void MyContactListener::EndContact(b2Contact* contact) {
	MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
	std::vector<MyContact>::iterator pos;
	pos = std::find(_contacts.begin(), _contacts.end(), myContact);
	if (pos != _contacts.end()) {
		_contacts.erase(pos);
	}
}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}














//void ContactListener::BeginContact(b2Contact* contact)
//{
//	b2Body* bodyA = contact->GetFixtureA()->GetBody();
//	b2Body* bodyB = contact->GetFixtureB()->GetBody();
//	CCSprite* spriteA = (CCSprite*)bodyA->GetUserData();
//	CCSprite* spriteB = (CCSprite*)bodyB->GetUserData();
//
//	CCLog("dsfffffffffffffffffffffffffffffffffffffffffffff");
//
//	//更改碰撞体颜色
//	if (spriteA != NULL && spriteB != NULL)
//	{
//		spriteA->setColor(ccMAGENTA);
//		spriteB->setColor(ccMAGENTA);
//	}
//}
//
//
//void ContactListener::EndContact(b2Contact* contact)
//{
//	b2Body* bodyA = contact->GetFixtureA()->GetBody();
//	b2Body* bodyB = contact->GetFixtureB()->GetBody();
//	CCSprite* spriteA = (CCSprite*)bodyA->GetUserData();
//	CCSprite* spriteB = (CCSprite*)bodyB->GetUserData();
//
//	//更改碰撞体颜色
//	if (spriteA != NULL && spriteB != NULL)
//	{
//		spriteA->setColor(ccWHITE);
//		spriteB->setColor(ccWHITE);
//	}
//}
//
//ContactListener::ContactListener()
//{
//
//}
//
//ContactListener::~ContactListener()
//{
//
//}
