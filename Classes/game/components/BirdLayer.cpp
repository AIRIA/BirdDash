#include "BirdLayer.h"
#include "game/models/Bird.h"
#include "game/utils/BirdUtil.h"

#define BIRD_WRAPPER_WIDTH 526
#define BIRD_WRAPPER_HEIGHT 650

bool BirdLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    BirdUtil::initAnimate();
    BirdUtil::initBirds();
    initBirds();
    return true;
}

void BirdLayer::initBirds()
{
    CCSize layerSize = CCSizeMake(BIRD_WRAPPER_WIDTH,BIRD_WRAPPER_HEIGHT);
    setContentSize(layerSize);
    float boxWidth = BIRD_WRAPPER_WIDTH/PP_COL;
    float boxHeight = 72;
	CCSprite *sprFrame = SPRITE_FRAME(box01_burn@2x.png);
    CCSpriteBatchNode *birdBatchNode = CCSpriteBatchNode::createWithTexture(sprFrame->getTexture());
	BirdUtil::featherBatchNode = CCSpriteBatchNode::createWithTexture(sprFrame->getTexture());
	birdBatchNode->setPosition(ccp(-BIRD_WRAPPER_WIDTH/2,0));
	BirdUtil::featherBatchNode->setPosition(birdBatchNode->getPosition());
	Bird **bird = BirdUtil::birds[0];
    for(int row=0; row<3; row++)
    {
        for(int col=0; col<PP_COL; col++)
        {
            (*bird)->setPosition(ccp(boxWidth*(col+0.5),boxHeight*row+40));
            (*bird)->eyeclose();
			(*bird)->reorderSelf();
            birdBatchNode->addChild(*bird);
			bird++;
        }
    }
    addChild(birdBatchNode);
	addChild(BirdUtil::featherBatchNode);
}
