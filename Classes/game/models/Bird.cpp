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
    CCString *birdName = CCString::createWithFormat("box0%d_normal_00@2x.png",type);
    bird->type = type;
    if(bird&&bird->initWithSpriteFrameName(birdName->getCString()))
    {
        bird->autorelease();
        return bird;
    }
    CC_SAFE_DELETE(bird);
    return NULL;
}

void Bird::eyeclose()
{

    int delayTime = rand()%5+2;
    CCActionInterval *delay = CCDelayTime::create(delayTime);
    CCCallFunc *handler = CCCallFunc::create(this,callfunc_selector(Bird::eyeclose));
    CCString *prefix = CCString::createWithFormat("box0%d",type);
    CCAnimate *animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(prefix->getCString()));
    CCSequence *eyeSeq = CCSequence::create(delay,animate,handler,NULL);
    runAction(eyeSeq);
}

void Bird::reorderSelf()
{
    if(getParent())
    {
        getParent()->reorderChild(this,PP_ROW-row);
    }
    else
    {
        setZOrder(PP_ROW-row);
    }
}

