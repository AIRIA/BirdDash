#include "ShakeBird.h"

ShakeBird * ShakeBird::createShakeBird(const char *pszName)
{
    ShakeBird *sb = new ShakeBird();
    if(sb&&sb->initWithSpriteFrameName(pszName))
    {
        sb->autorelease();
        sb->setBeganTarget(sb,menu_selector(ShakeBird::shake));
    }
    return sb;
}

void ShakeBird::shake(CCObject *pSender)
{
    setTouchEnabled(false);
    srand((unsigned)time(NULL));
	startShake();
}

void ShakeBird::startShake()
{
    shakeTimes++;
    if(shakeTimes==35)
    {
		
        return ;
    }
    int moveX = rand()%3+1;
    int moveY = rand()%3+1;
    int xDirc = rand()%2;
    int yDirc = rand()%2;
    if(xDirc)
    {
        moveX *= -1;
    }
    if(yDirc)
    {
        moveY *= -1;
    }
    CCActionInterval *shakeAction = CCMoveBy::create(0.02f,ccp(moveX,moveY));
    CCCallFunc *callback = CCCallFunc::create(this,callfunc_selector(ShakeBird::startShake));
    runAction(CCSequence::create(shakeAction,shakeAction->reverse(),callback,NULL));
}

