#include "BirdUtil.h"

#define ACT_TIME 1.5f

CCSpriteBatchNode *BirdUtil::featherBatchNode = NULL;
Bird *BirdUtil::birds[PP_ROW][PP_COL] = {};
BirdUtil *BirdUtil::_instance = NULL;

BirdUtil *BirdUtil::getInstance()
{
    if(!_instance)
    {
        _instance = new BirdUtil();
    }
    return _instance;
}

void BirdUtil::createRandomFeather( CCNode *bird,const char *feather,int featherNum )
{
    CCSprite *featherSpr = CCSprite::createWithSpriteFrameName(feather);
    CCPoint birdPos = bird->getPosition();
    for(int i=0; i<featherNum; i++)
    {
        CCSprite *birdFeather = CCSprite::createWithSpriteFrameName(feather);
        birdFeather->setPosition(birdPos);
        CCPoint randomPoint = createRandomPoint(birdPos,70);
        float scaleFac = (rand()%10)*0.1+0.5;
        birdFeather->setScale(scaleFac);
        CCActionInterval *moveAct = CCMoveTo::create(0.1f,randomPoint);
        CCRotateTo *rotateTo = CCRotateTo::create(0.2f,0);
        CCMoveBy *moveDown = CCMoveBy::create(ACT_TIME,ccp(0,-40));
        CCActionInterval *fadeOut = CCFadeOut::create(ACT_TIME);
        CCActionInterval *rl = CCRotateBy::create(0.2f,25);
        CCActionInterval *rr = CCRotateBy::create(0.2f,-25);
        CCCallFuncN *rmFeather = CCCallFuncN::create(BirdUtil::getInstance(),callfuncN_selector(BirdUtil::removeFeather));
        CCSequence *rotateSeq = CCSequence::create(rotateTo,rl,rl->reverse(),rr,rr->reverse(),rl,NULL);
        CCSpawn *fly = CCSpawn::create(fadeOut,rotateSeq,moveDown,NULL);
        CCSequence *seqAct = CCSequence::create(moveAct,fly,rmFeather,NULL);
        int rotate = rand()%360;
        birdFeather->setRotation(rotate);
        birdFeather->runAction(seqAct);
        featherBatchNode->addChild(birdFeather);
    }

}

cocos2d::CCPoint BirdUtil::createRandomPoint( CCPoint pos,int range )
{
    int min = 25;
    int x = rand()%(range-min)+min,
        y = rand()%(range-min)+min,
        direcX = rand()%2,
        direcY = rand()%2;
    direcX = direcX==0?-1:1;
    direcY = direcY==0?-1:1;
    x *= direcX;
    y *= direcY;
    return CCPointMake(pos.x+x,pos.y+y);
}

void BirdUtil::initBirds()
{
    srand((unsigned)time(NULL));
    for(int row=2; row>=0; row--)
    {
        for(int col=6; col>=0; col--)
        {
            int type = rand()%5;
            Bird *bird = Bird::createBird(type);
            bird->row = row;
            bird->col = col;
            birds[row][col] = bird;
        }
    }
}

void BirdUtil::initAnimate()
{
    CCAnimationCache *animationCache = CCAnimationCache::sharedAnimationCache();
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    for(int i=0; i<8; i++)
    {
        CCArray *frames = CCArray::createWithCapacity(2);
        CCString *s1 = CCString::createWithFormat("box0%d_normal_00@2x.png",i);
        CCString *s2 = CCString::createWithFormat("box0%d_normal_02@2x.png",i);
        CCSpriteFrame *frame1 = frameCache->spriteFrameByName(s1->getCString());
        CCSpriteFrame *frame2 = frameCache->spriteFrameByName(s2->getCString());
        frames->addObject(frame1);
        frames->addObject(frame2);
        frames->addObject(frame1->copy());
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames,0.2f);
        CCString *aniName = CCString::createWithFormat("box0%d",i);
        animationCache->addAnimation(animation,aniName->getCString());
    }
}

void BirdUtil::removeFeather( CCNode *node )
{
    node->removeFromParentAndCleanup(true);
}

void BirdUtil::updateColPosition( int col )
{
    for(int i=1; i<PP_ROW; i++)
    {
        Bird *bird = BirdUtil::birds[i][col];
        if(!bird)
        {
            continue;
        }
        int num=0;
        for(int j=0; j<i; j++)
        {
            if(BirdUtil::birds[j][col]==NULL)
            {
                num++;
            }
        }
        if(num)
        {
            BirdUtil::birds[i][col]=NULL;
            int endPosY = BOX_HEIGHT*(i-num)+40;
            bird->row -= num;
            BirdUtil::birds[bird->row][col]=bird;
            CCActionInterval *moveAct = CCMoveTo::create(num*BOX_DOWN_TIME,ccp(bird->getPositionX(),endPosY));
            CCCallFunc *moveHandler = CCCallFunc::create(bird,callfunc_selector(Bird::shake));
            bird->runAction(CCSequence::create(moveAct,moveHandler,NULL));
            bird->reorderSelf();
        }
    }
}

void BirdUtil::checkAlltoDrop()
{
    CCSet *neighborSet = CCSet::create();
    for(int i=0; i<PP_ROW; i++)
    {
        int prevType = -1;
        int currentType = -1;
        for (int j=0; j<PP_COL; j++)
        {
            Bird *bird = birds[i][j];
            if(bird)
            {
                neighborSet->addObject(bird);
                currentType = bird->type;
                CCSet *res = bird->getNeighbor();
                if(res->count()==0)
                {

                }
                else
                {
                    //neighborSet->a
                }

            }

        }
    }
}
