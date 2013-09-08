#include "PauseLayer.h"

bool PauseLayer::init()
{
    do
    {
        CC_BREAK_IF(!CCLayer::init());
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
	bgLayer = CCLayerColor::create(ccc4(0,0,0,200));
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
	CCNode *menuNode = CCNode::create();
	CCMenuItemSprite *resumeGame = CCMenuItemSprite::create(SPRITE_FRAME(paused_resume_normal_china.png),SPRITE_FRAME(paused_resume_push_china.png));
	CCMenuItemSprite *restartGame = CCMenuItemSprite::create(SPRITE_FRAME(paused_restart_normal_china.png),SPRITE_FRAME(paused_restart_push_china.png));
	CCMenuItemSprite *quitGame = CCMenuItemSprite::create(SPRITE_FRAME(paused_quit_normal_china.png),SPRITE_FRAME(paused_quit_push_china.png));
	CCMenu *gameMenu = CCMenu::create(resumeGame,restartGame,quitGame,NULL);
	gameMenu->alignItemsVerticallyWithPadding(15);
	CCSprite *menuBg = SPRITE_FRAME(paused_bg.png);
	menuNode->setPosition(ccp(VisibleRect::center().x,-232));
	menuNode->addChild(menuBg);
	menuNode->addChild(gameMenu);
	gameMenu->setPosition(ccp(65,-60));
	CCActionInterval *moveAct = CCMoveTo::create(0.3f,ccp(VisibleRect::center().x,232));
	menuNode->runAction(moveAct);
	addChild(menuNode);
}

