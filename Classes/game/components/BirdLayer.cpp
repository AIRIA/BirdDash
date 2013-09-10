#include "BirdLayer.h"
#include "game/models/Bird.h"
#include "game/utils/BirdUtil.h"

bool BirdLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
	BirdUtil::initAnimate();
    CCLayerColor *layerColor = CCLayerColor::create(ccc4(0,0,0,0));
	layerColor->ignoreAnchorPointForPosition(false);
	layerColor->setAnchorPoint(ccp(0.5,0));
	CCSize layerSize = CCSizeMake(526,650);
	setContentSize(layerSize);
	layerColor->setContentSize(layerSize);
	float block = 526/7;
	for(int i=7;i>=0;i--){
		Bird *bird = Bird::createBird(i);
		bird->setPosition(ccp(block*0.5,72*i+40));
		layerColor->addChild(bird);
		bird->eyeclose();
	}
	
    addChild(layerColor);
    return true;
}
