﻿#include "Bird.h"
#include "game/utils/BirdUtil.h"

bool Bird::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    if(isContainPoint(pTouch))
    {
        CCLog("select bird positionY:%f,at row %d",getPositionY(),row);
    }
    if(isContainPoint(pTouch)&&isDragable()&&dragable)
    {
        return true;
    }
    return false;
}

void Bird::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    updatePosition(pTouch);
}

void Bird::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

    if(isFlying)
    {
        int num=0;
        for(int i=0; i<row; i++)
        {
            if(BirdUtil::birds[i][col]==NULL)
            {
                num++;
            }
        }
        row-=num;
        CCActionInterval *moveAct = CCMoveTo::create(BOX_DOWN_TIME*num+0.05f,ccp(BOX_WIDTH*(col+0.5),BOX_HEIGHT*row+40));
        CCCallFunc *moveEnd = CCCallFunc::create(this,callfunc_selector(Bird::shake));
        runAction(CCSequence::create(moveAct,moveEnd,NULL));
        reorderSelf();
        BirdUtil::birds[row][col] = this;
    }
    else
    {
        shake();
    }
    BirdUtil::checkAlltoDrop();
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
    SimpleAudioEngine::sharedEngine()->playEffect("sounds/SFX/Bird_droped.mp3");
    isFlying = false;
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
    int featherNum = rand()%2+1;
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

void Bird::updatePosition(CCTouch *pTouch)
{

    //转化到相对于父容器的坐标
    CCPoint pos = getParent()->convertToNodeSpaceAR(pTouch->getLocation());
    float minX = BOX_WIDTH/2;
    float maxX = BIRD_WRAPPER_WIDTH-BOX_WIDTH/2;
    float minY = 45;
    float maxY = BIRD_WRAPPER_HEIGHT-60;
    pos.x = pos.x<minX?minX:pos.x;
    pos.x = pos.x>maxX?maxX:pos.x;
    pos.y = pos.y<minY?minY:pos.y;
    pos.y = pos.y>maxY?maxY:pos.y;

    int currentCol = (pos.x-BOX_WIDTH*0.5)/BOX_WIDTH;
    int currentRow = (pos.y-40)/BOX_HEIGHT;
    float remainX = (int)(pos.x-BOX_WIDTH*0.5)%BOX_WIDTH;
    float remainY = (int)(pos.y-40)%BOX_HEIGHT;
    if(remainX>BOX_WIDTH/2)
    {
        currentCol++;
    }
    if(remainY>40)
    {
        currentRow++;
    }
    if(BirdUtil::birds[currentRow][currentCol]==NULL)
    {
        reorderSelf();
        isFlying = true;
        BirdUtil::birds[row][col] = NULL;
        BirdUtil::updateColPosition(col,row);
        row = currentRow;
        col = currentCol;
        //限制小鸟重叠
        //如果左 左下 右 右下 和下方有小鸟的话 就限制位置
        int leftCol = col==0?col:col-1;
        int rightCol = col==(PP_COL-1)?col:col+1;
        Bird *left = BirdUtil::birds[row][leftCol];
        Bird *right = BirdUtil::birds[row][rightCol];
        if(leftCol!=col&&left&&pos.x<(left->getPositionX()+BOX_WIDTH))
        {
            pos.x = left->getPositionX()+BOX_WIDTH;
        }
        if(rightCol!=col&&right&&pos.x>(right->getPositionX()-BOX_WIDTH))
        {
            pos.x = right->getPositionX()-BOX_WIDTH;
        }
        setPosition(ccp(pos.x,pos.y+30));
    }
}

void Bird::getNeighbors(CCArray *neighbors)
{
    if(neighbors->containsObject(this))
    {
        return;
    }
    else
    {
        neighbors->addObject(this);
        isChecked = true;
    }
    int leftCol = col==0?col:col-1;
    int rightCol = col==(PP_COL-1)?col:col+1;
    int downRow = row==0?row:row-1;
    int upRow = row==(PP_ROW-1)?row:row+1;
    Bird *left = BirdUtil::birds[row][leftCol];
    Bird *right = BirdUtil::birds[row][rightCol];
    Bird *up = BirdUtil::birds[upRow][col];
    Bird* down = BirdUtil::birds[downRow][col];
    if(leftCol!=col&&left&&type==left->type)
    {
        left->getNeighbors(neighbors);
    }
    if(rightCol!=col&&right&&type==right->type)
    {
        right->getNeighbors(neighbors);
    }
    if(downRow!=row&&down&&type==down->type)
    {
        down->getNeighbors(neighbors);
    }
    if(upRow!=row&&up&&type==up->type)
    {
        up->getNeighbors(neighbors);
    }
    return;
}

void Bird::shakeBody(CCNode *node,void *birdDashInfo)
{
    shakeTimes++;
    if(shakeTimes==30)
    {
        DashInfo *di = (DashInfo*)birdDashInfo;
        SimpleAudioEngine::sharedEngine()->playEffect("sounds/SFX/Bird_remove(2).mp3");
        featherFly();
        BirdUtil::birds[row][col] = NULL;
        di->neighbors->removeObject(this);
        removeFromParentAndCleanup(true);
        if(di->neighbors->count()==0)
        {
            std::set<int>::iterator t1 = di->cols.begin();
            CCLog("for update col num %d",di->cols.size());
            while(t1!=di->cols.end())
            {
                BirdUtil::updateColPosition(*t1);
                t1++;
            }
            di->cols.clear();
            delete di;
            BirdUtil::checkAlltoDrop();
        }
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
    CCCallFuncND *callback = CCCallFuncND::create(this,callfuncND_selector(Bird::shakeBody),birdDashInfo);
    runAction(CCSequence::create(shakeAction,shakeAction->reverse(),callback,NULL));
}

