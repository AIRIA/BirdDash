#ifndef _BIRD_H_
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
	void eyeclose();
}; 

#endif // !_BIRD_H_
