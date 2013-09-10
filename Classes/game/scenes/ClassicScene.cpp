#include "ClassicScene.h"
#include "base/BaseSprite.h"
#include "game/components/PauseLayer.h"
#include "game/components/ExitWin.h"

bool ClassicScene::init()
{
    do
    {
        CC_BREAK_IF(!BaseScene::init());
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/BGM/Play_bgm_long.mp3",true);
        initBg();
        return true;
    }
    while (0);
    return false;
}

void ClassicScene::initBg()
{
    CCSprite *bg = SPRITE(images/stage_classic/stage_bg_RETINA.png);
    bg->setPosition(VisibleRect::center());
    addChild(bg);
    CCSprite *bgWood = SPRITE(images/stage_classic/stage_tree_RETINA.png);
    CCSprite *floor = SPRITE(images/stage_classic/stage_tree_grass_RETINA.png);
    floor->setPosition(ccp(VisibleRect::center().x,44));
    bgWood->setPosition(ccp(VisibleRect::center().x,-400));
    CCActionInterval *moveAct = CCMoveTo::create(0.6f,ccp(VisibleRect::center().x,400));
    bgWood->runAction(moveAct);
    addChild(bgWood);
    birdLayer = BirdLayer::create();
	birdLayer->setPosition(ccp(VisibleRect::center().x,-800));
	CCActionInterval *birdLayerMove = CCMoveTo::create(0.6f,ccp(VisibleRect::center().x,40));
	birdLayer->runAction(birdLayerMove);
	addChild(birdLayer);
    addChild(floor);
    BaseSprite *pauseBtn = BaseSprite::createFromFile("images/stage_classic/stage_dimm2_RETINA.png","sounds/SFX/pausebuttonclick.mp3");
    pauseBtn->setPosition(ccp(50,VisibleRect::top().y-50));
    pauseBtn->setOpacity(0);
    pauseBtn->setBeganTarget(this,menu_selector(ClassicScene::pauseGame));
    addChild(pauseBtn);
}

void ClassicScene::loadAsset()
{
    frameCache->addSpriteFramesWithFile("images/stage_classic/stage_RETINA.plist");
    frameCache->addSpriteFramesWithFile("images/stage_classic/numbers_RETINA.plist");
    frameCache->addSpriteFramesWithFile("images/stage_classic/stage_CN_RETINA.plist");
    frameCache->addSpriteFramesWithFile("images/pause/paused_RETINA.plist");
    frameCache->addSpriteFramesWithFile("images/pause/paused_CN_RETINA.plist");
	frameCache->addSpriteFramesWithFile("images/character/Character_RETINA.plist");
}

void ClassicScene::pauseGame(CCObject *pSender)
{
    PauseLayer *pl = PauseLayer::create();
    addChild(pl);
}


void ClassicScene::keyBackClicked()
{
    if(isShowExit)
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(RESUME_GAME);
        isShowExit = false;
    }
    else
    {
        addChild(ExitWin::create());
        isShowExit = true;
    }


}


