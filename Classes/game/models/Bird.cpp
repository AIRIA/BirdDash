#include "Bird.h"

bool Bird::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(isContainPoint(pTouch))
	{
		return true;
	}
	return false;
}

void Bird::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void Bird::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

Bird * Bird::createBird( int type )
{
	Bird *bird = new Bird();
	CCString *birdName = CCString::createWithFormat("",type);
	if(bird&&bird->initWithFile(birdName->getCString()))
	{
		bird->autorelease();
		return bird;
	}
	CC_SAFE_DELETE(bird);
	return NULL;
}

