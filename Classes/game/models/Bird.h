﻿#ifndef _BIRD_H_
#define _BIRD_H_

#include "common/CommonHeaders.h"
#include "base/BaseSprite.h"

class Bird:public BaseSprite
{
public:
	int row;
	int col;
	int type;
	int state;
	bool dragable;
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	static Bird *createBird(int type);
	virtual void onEnter();
	void eyeclose();
	void reorderSelf();
	/* 缩动身体后 随机掉落羽毛 */
	void shake();
	/* 飘落羽毛 */
	void featherFly();
}; 

#endif // !_BIRD_H_
