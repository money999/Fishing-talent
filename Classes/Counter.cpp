#include "Counter.h"

enum{
	k_Counter_Action = 0
};


Counter::Counter()
{
	_digit = 0;
}

Counter::~Counter()
{

}

Counter* Counter::create( CCArray* presenters, int digit )
{
	Counter* counter = new Counter();
	counter->autorelease();
	counter->init(presenters, digit);
	return counter;
}

bool Counter::init(CCArray* presenters, int digit)
{
	CCNode::init();
	_presenters = CCNode::create();
	CCObject* iterator;
	int i = 0;
	CCARRAY_FOREACH(presenters, iterator)
	{
		CCNode* node = (CCNode*)iterator;
		int y = node->getContentSize().height * i;
		node->setPosition(0,y);
		_presenters->addChild(node,0,i);//孩子的编号从0编到9
		i++;
	}
	this->addChild(_presenters);
	this->setDigit(digit);
	return true;
}

void Counter::setDigit( int digit )
{
	if(digit != _digit)
	{
		_digit = digit;
		animation(digit);
	}
}

void Counter::animation( int digit )
{
	CCNode* pres = _presenters->getChildByTag(digit);
	CCPoint dest = pres->getPosition();
	_presenters ->stopActionByTag(k_Counter_Action);
	CCMoveTo* move = CCMoveTo::create(0.5, CCPointMake(0, -dest.y));
	CCFiniteTimeAction* seq = CCSequence::create(move,NULL);
	seq->setTag(k_Counter_Action);
	_presenters->runAction(seq);
}

void Counter::visit()
{
	glEnable(GL_SCISSOR_TEST);
	CCNode* presenter = _presenters->getChildByTag(_digit);
	CCSize size = presenter->getContentSize();
	CCPoint location = this->getParent()->convertToWorldSpace(CCPointMake(this->getPosition().x-size.width*0.5, this->getPosition().y-size.height*0.5));
	glScissor(location.x, location.y, size.width, size.height);
	CCNode::visit();
	glDisable(GL_SCISSOR_TEST);
}
