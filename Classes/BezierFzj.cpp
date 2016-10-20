#include "BezierFzj.h"
#include "Fish.h"
BezierFzj::BezierFzj()
{

}

BezierFzj::~BezierFzj()
{

}

bool BezierFzj::init(float time, ccBezierConfig value)
{
	
	return BezierFzj::initWithDuration(time, value);
}

BezierFzj* BezierFzj::create(float time, ccBezierConfig value )
{
	BezierFzj *tt = new BezierFzj();
	tt->init(time, value);
	tt->autorelease();
	return tt;
}

/************************************************************************/
/* ����������㷨��û�ÿ��Ƶ�߶�, ��л������̵�����취             */
/************************************************************************/
cocos2d::CCPoint BezierFzj::getCon( CCPoint p1, CCPoint p2 , float hei)
{
	CCPoint midP = ccpMidpoint(p1, p2);
	CCPoint vec1 = ccpSub(p1, p2);
	float tx = vec1.x;
	float ty = vec1.y;
	vec1.x = -ty;//����ת90�ȣ�����ʱ����ת���ó˾���İ취��
	vec1.y = tx;
	float dis = ccpDistance(vec1, ccp(0.0f,0.0f));
	vec1.x = vec1.x/dis;//�õ���λ����
	vec1.y = vec1.y/dis;
	vec1.x = vec1.x * hei;//���ϲ����õ������ϵ�ƫ�Ƶ�
	vec1.y = vec1.y * hei;
	CCPoint ttt = ccpAdd(vec1,midP);
	return ttt;
}
/************************************************************************/
/* �������ľ�����ʵ����,�յ㲻Ҫ�������ʼ����                         */
/************************************************************************/
CCActionInterval* BezierFzj::createBezierFzj( float time, CCPoint start, CCPoint end, float control1, float control2 )
{
	CCPoint spp,epp,mid;
	spp = start;
	epp = end;
	mid = ccpMidpoint(spp,epp);

	CCPoint con1,con2;
	con1 = getCon(spp,mid,control1);
	con2 = getCon(mid,epp,control2);

	ccBezierConfig tr0;
	tr0.endPosition=ccpSub(mid,spp);
	tr0.controlPoint_1=ccpSub(con1, spp);
	tr0.controlPoint_2=tr0.controlPoint_1;

	ccBezierConfig tr1;
	tr1.endPosition=ccpSub(epp,mid);
	tr1.controlPoint_1=ccpSub(con2, mid);
	tr1.controlPoint_2=tr1.controlPoint_1;

	CCActionInterval* bezierForward1 = BezierFzj::create(time * 0.5,tr0);
	CCActionInterval* bezierForward2 = BezierFzj::create(time * 0.5,tr1);

	CCActionInterval *tt = CCSequence::create(bezierForward1, bezierForward2, NULL);
	return tt;
}

void BezierFzj::update( float time )
{
	CCPoint nowPoint = m_pTarget->getPosition();
	CCBezierBy::update(time);
	CCPoint previousPoint = m_previousPosition;
	//CCLog("%f %f %f %f",nowPoint.x, nowPoint.y, previousPoint.x, previousPoint.y);
	float angle = ccpAngleSigned(ccpSub(previousPoint, nowPoint),ccp(0.0f,1.0f));
	if(m_pTarget->getTag() == k_Fish_Tag && m_pTarget->getChildrenCount() == 1)
	{
		CCArray *tt = m_pTarget->getChildren();
		CCSprite * sp = (CCSprite *)tt->objectAtIndex(0);
	   //CCSprite * sp = (CCSprite *)m_pTarget->getChildByTag(999);//Ϊʲô���ﲻ����tag���벻������,����ȡ�������ǿա�fish���м�tag�����ԣ�������ǲ����ã���ΪҪ������������ĽǶȣ�Ҫ�þ���ĽǶȣ����ǽڵ�ĽǶ�
		if(sp)
			sp->setRotation(CC_RADIANS_TO_DEGREES(angle) + 90);
	}
	else
		m_pTarget->setRotation(CC_RADIANS_TO_DEGREES(angle) + 90);
}

