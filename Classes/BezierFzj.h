#pragma once

#include "cocos2d.h"
USING_NS_CC;

class BezierFzj : public CCBezierBy
{
public:
	BezierFzj();
	~BezierFzj();
	bool init(float time, ccBezierConfig value);
	
	virtual void update(float time);
	static BezierFzj* create(float time, ccBezierConfig value);
	static CCActionInterval* createBezierFzj(float time, CCPoint start, CCPoint end, float control1, float control2);
	static CCPoint getCon( CCPoint p1, CCPoint p2 , float hei);
protected:

private:

};
