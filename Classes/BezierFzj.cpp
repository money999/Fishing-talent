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
/* 用向量相关算法获得获得控制点高度, 感谢汤大神教的这个办法             */
/************************************************************************/
cocos2d::CCPoint BezierFzj::getCon( CCPoint p1, CCPoint p2 , float hei)
{
	CCPoint midP = ccpMidpoint(p1, p2);
	CCPoint vec1 = ccpSub(p1, p2);
	float tx = vec1.x;
	float ty = vec1.y;
	vec1.x = -ty;//向量转90度，按逆时针旋转（用乘矩阵的办法）
	vec1.y = tx;
	float dis = ccpDistance(vec1, ccp(0.0f,0.0f));
	vec1.x = vec1.x/dis;//得到单位向量
	vec1.y = vec1.y/dis;
	vec1.x = vec1.x * hei;//乘上步长得到法线上的偏移点
	vec1.y = vec1.y * hei;
	CCPoint ttt = ccpAdd(vec1,midP);
	return ttt;
}
/************************************************************************/
/* 传进来的就是真实坐标,终点不要再相对起始点了                         */
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
	   //CCSprite * sp = (CCSprite *)m_pTarget->getChildByTag(999);//为什么这里不能用tag就想不明白了,反正取出来都是空。fish中有加tag并测试，这里就是不能用，因为要更新物理世界的角度，要用精灵的角度，不是节点的角度
		if(sp)
			sp->setRotation(CC_RADIANS_TO_DEGREES(angle) + 90);
	}
	else
		m_pTarget->setRotation(CC_RADIANS_TO_DEGREES(angle) + 90);
}

