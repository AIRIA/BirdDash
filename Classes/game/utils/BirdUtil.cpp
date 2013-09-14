#include "BirdUtil.h"

#define ACT_TIME 1.5f

CCSpriteBatchNode *BirdUtil::featherBatchNode = NULL;
Bird *BirdUtil::birds[PP_ROW][PP_COL] = {};
BirdUtil *BirdUtil::_instance = NULL;
std::set<int> BirdUtil::cols;

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
    for(int row=3; row>=0; row--)
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
    CCLog("updateColPosition");
    int currentRow = 0;
    for(int i=0; i<PP_ROW; i++)
    {
        Bird *bird = BirdUtil::birds[i][col];
        if(bird&&bird->dragable)
        {
            if(bird->row!=currentRow)
            {
                BirdUtil::birds[bird->row][col]=NULL;
                BirdUtil::birds[currentRow][col]=bird;
                int range = bird->row - currentRow;
                bird->row = currentRow;
                CCActionInterval *moveAct = CCMoveTo::create(range*BOX_DOWN_TIME,ccp(bird->getPositionX(),currentRow*BOX_HEIGHT+40));
                CCCallFunc *moveHandler = CCCallFunc::create(bird,callfunc_selector(Bird::shake));
                bird->runAction(CCSequence::create(moveAct,moveHandler,NULL));
                bird->reorderSelf();
            }
            currentRow++;
        }
    }
}

void BirdUtil::checkAlltoDrop()
{

    int times=0;
    for(int i=0; i<PP_ROW; i++)
    {
        for (int j=0; j<PP_COL; j++)
        {
            Bird *bird = BirdUtil::birds[i][j];
            if(bird&&bird->isChecked==false)
            {
                DashInfo *dashInfo = new DashInfo();
                times++;
                bird->getNeighbors(dashInfo->neighbors);
                CCObject *obj = NULL;
                Bird *neighbor;
                if(dashInfo->neighbors->count()>=3)
                {

                    SimpleAudioEngine::sharedEngine()->playEffect("sounds/SFX/Bird_vibration.mp3");

                    CCARRAY_FOREACH(dashInfo->neighbors,obj)
                    {
                        neighbor = (Bird*)obj;
                        (dashInfo->cols).insert(neighbor->col);
                        neighbor->dragable = false;
                        neighbor->shakeBody(NULL,dashInfo);
                        neighbor->isChecked = true;
                        //BirdUtil::birds[neighbor->row][neighbor->col] = NULL;
                    }

                }
                else
                {
                    CCARRAY_FOREACH(dashInfo->neighbors,obj)
                    {
                        neighbor = (Bird*)obj;
                        neighbor->isChecked = false;
                    }
					dashInfo->neighbors->removeAllObjects();
					delete dashInfo;
                }

            }
        }
    }

    CCLog("run times:%d",times);
}

void BirdUtil::resetAlltoUncheck()
{
    for(int i=0; i<PP_ROW; i++)
    {
        for (int j=0; j<PP_COL; j++)
        {
            Bird *bird = BirdUtil::birds[i][j];
            if(bird&&bird->isChecked==true)
            {
                bird->isChecked =false;
            }
        }
    }
}
