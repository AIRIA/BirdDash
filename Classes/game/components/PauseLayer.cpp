#include "PauseLayer.h"
#include "game/GameMain.h"
#include "base/BaseMenuSprite.h"
#include "base/MaskLayer.h"

#define PAUSE_SLIDE_TIME 0.3f

enum
{
    kPauseMenu=110
};

bool PauseLayer::init()
{
    do
    {
        CC_BREAK_IF(!CCLayer::init());
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		setTouchEnabled(true);
        initBgLayer();
        initMenu();
        return true;
    }
    while (0);
    return false;
}

void PauseLayer::initBgLayer()
{
    bgLayer = CCLayerColor::create(ccc4(0,0,0,0));
    bgLayer->ignoreAnchorPointForPosition(true);
    bgLayer->setContentSize(CCDirector::sharedDirector()->getWinSize());
    bgLayer->setOpacity(0);
    CCActionInterval *fadeIn = CCFadeTo::create(0.5,200);
    bgLayer->runAction(fadeIn);
    addChild(bgLayer);
}

void PauseLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1,true);
}

void PauseLayer::initMenu()
{
    menuNode = CCNode::create();
    CCMenuItemSprite *resumeGame = BaseMenuSprite::createMenuSprite(SPRITE_FRAME(paused_resume_normal_china.png),SPRITE_FRAME(paused_resume_push_china.png),NULL,this,menu_selector(PauseLayer::resumeHandler),"sounds/SFX/buttonclick.mp3");
    CCMenuItemSprite *restartGame = BaseMenuSprite::createMenuSprite(SPRITE_FRAME(paused_restart_normal_china.png),SPRITE_FRAME(paused_restart_push_china.png),NULL,NULL,NULL,"sounds/SFX/buttonclick.mp3");
    CCMenuItemSprite *quitGame = BaseMenuSprite::createMenuSprite(SPRITE_FRAME(paused_quit_normal_china.png),SPRITE_FRAME(paused_quit_push_china.png),NULL,this,menu_selector(PauseLayer::quitHandler),"sounds/SFX/buttonclick.mp3");
    gameMenu = CCMenu::create(resumeGame,restartGame,quitGame,NULL);
    gameMenu->alignItemsVerticallyWithPadding(15);
    CCSprite *menuBg = SPRITE_FRAME(paused_bg.png);
    menuNode->setPosition(ccp(VisibleRect::center().x,-232));
    menuNode->addChild(menuBg);
    menuNode->addChild(gameMenu);
    gameMenu->setPosition(ccp(65,-60));
    CCActionInterval *moveAct = CCMoveTo::create(PAUSE_SLIDE_TIME,ccp(VisibleRect::center().x,232));
    menuNode->runAction(moveAct);
    addChild(menuNode);
}

void PauseLayer::resumeHandler( CCObject *pSender )
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CCActionInterval *moveDown = CCMoveTo::create(PAUSE_SLIDE_TIME,ccp(VisibleRect::center().x,-232));
    CCActionInterval *fadeOut = CCFadeTo::create(PAUSE_SLIDE_TIME,0);
    bgLayer->runAction(fadeOut);
    CCCallFunc *destroyHandler = CCCallFunc::create(this,callfunc_selector(PauseLayer::destroy));
    CCSequence *seqAct = CCSequence::create(moveDown,destroyHandler,NULL);
    menuNode->runAction(seqAct);
}

void PauseLayer::destroy()
{
    removeFromParentAndCleanup(true);
}

void PauseLayer::quitHandler( CCObject *pSender )
{
    CCDirector::sharedDirector()->replaceScene(GameMain::create());
}

bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent)
{
	return true;
}