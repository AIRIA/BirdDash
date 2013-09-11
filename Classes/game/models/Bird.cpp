#include "Bird.h"
#include "game/utils/BirdUtil.h"

bool Bird::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    if(isContainPoint(pTouch)&&isDragable())
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
    SimpleAudioEngine::sharedEngine()->playEffect("sounds/SFX/Bird_droped.mp3");
    shake();
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

void Bird::shake()
{
    CCActionInterval *scaleIn = CCScaleBy::create(0.1f,0.8f,1.2f);
    CCCallFunc *shakeHandler = CCCallFunc::create(this,callfunc_selector(Bird::featherFly));
    CCActionInterval *scaleOut = CCEaseElasticOut::create(CCScaleTo::create(0.6f,1));
    CCSequence *scaleSeq = CCSequence::create(scaleIn,shakeHandler,scaleOut,NULL);
    runAction(scaleSeq);
}

void Bird::onEnter()
{
    CCSprite::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void Bird::featherFly()
{
    CCString *featherName = CCString::createWithFormat("box0%d_feather@2x.png",type);
    int featherNum = rand()%3+2;
    BirdUtil::createRandomFeather(this,featherName->getCString(),featherNum);
}

bool Bird::isDragable()
{
    int rowUp = row==PP_ROW-1?row:row+1;
    CCPoint up = ccp(rowUp,col);
    int colRight = col==(PP_COL-1)?col:col+1;
    CCPoint right = ccp(row,colRight);
    int colLeft = col==0?col:col-1;
    CCPoint left = ccp(row,colLeft);
    CCPoint points[3] = {up,right,left};
    for(int i=0; i<3; i++)
    {
        CCPoint p = points[i];
        int row = p.x,col = p.y;
        if(BirdUtil::birds[row][col]==NULL)
        {
            return true;
        }
    }
    return false;
}

