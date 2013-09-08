#include "BirdUtil.h"

#define ACT_TIME 1.5f

CCSpriteBatchNode *BirdUtil::featherBatchNode = NULL;

void BirdUtil::createRandomFeather( CCNode *bird,const char *feather,int featherNum )
{
    CCSprite *featherSpr = CCSprite::createWithSpriteFrameName(feather);
    CCPoint birdPos = bird->getPosition();
    featherBatchNode = CCSpriteBatchNode::createWithTexture(featherSpr->getTexture());
	featherBatchNode->setPosition(CCPointZero);
	srand((unsigned)time(NULL));
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
		CCSequence *rotateSeq = CCSequence::create(rotateTo,rl,rl->reverse(),rr,rr->reverse(),rl,NULL);
		CCSpawn *fly = CCSpawn::create(fadeOut,rotateSeq,moveDown,NULL);
		CCSequence *seqAct = CCSequence::create(moveAct,fly,NULL);
        int rotate = rand()%360;
        birdFeather->setRotation(rotate);
        birdFeather->runAction(seqAct);
		featherBatchNode->addChild(birdFeather);
    }
	bird->getParent()->getParent()->addChild(featherBatchNode);
	bird->removeFromParentAndCleanup(true);
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
