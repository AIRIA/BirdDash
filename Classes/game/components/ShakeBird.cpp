#include "ShakeBird.h"
#include "game/utils/BirdUtil.h"

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
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/SFX/Bird_vibration.mp3");
}

void ShakeBird::startShake()
{
    shakeTimes++;
    if(shakeTimes==30)
    {
		SimpleAudioEngine::sharedEngine()->playEffect("sounds/SFX/Bird_remove(2).mp3");
		CCString *featherName = CCString::createWithFormat("box0%d_feather@2x.png",featherId);
		BirdUtil::createRandomFeather(this,featherName->getCString(),10);
		removeFromParentAndCleanup(true);
		shakeTimes = 0;
        return ;
    }
    int moveX = rand()%4+1;
    int moveY = rand()%4+1;
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

