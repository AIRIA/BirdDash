#include "ExitWin.h"

bool ExitWin::init()
{
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        initBgLayer();
        CCSprite *winBg = CCSprite::create("images/exit/exit_bg.png");
        winBg->setPosition(VisibleRect::center());
        CCMenuItemSprite *yes = CCMenuItemSprite::create(SPRITE(images/exit/exit_yes_normal.png),SPRITE(images/exit/exit_yes_push.png),this,menu_selector(ExitWin::exitGame));
        CCMenuItemSprite *no = CCMenuItemSprite::create(SPRITE(images/exit/exit_no_normal.png),SPRITE(images/exit/exit_no_push.png),this,menu_selector(ExitWin::resumeGame));
        CCMenu *exitMenu = CCMenu::create(yes,no,NULL);
        exitMenu->alignItemsHorizontally();
        addChild(winBg);
        exitMenu->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-70));
        addChild(exitMenu);
        CCNotificationCenter::sharedNotificationCenter()->postNotification(SHOW_EXIT_WIN);
        return true;
    }
    while (0);
    return false;
}

void ExitWin::initBgLayer()
{
    bgLayer = CCLayerColor::create(ccc4(0,0,0,0));
    bgLayer->setOpacity(0);
    bgLayer->setTouchPriority(-128);
    bgLayer->setTouchEnabled(false);
    CCActionInterval *fadeIn = CCFadeTo::create(0.5,100);
    bgLayer->runAction(fadeIn);
    addChild(bgLayer);
}

void ExitWin::exitGame( CCObject *pSender )
{
    CCDirector::sharedDirector()->end();
#if (CC_PLATFORM_ANDROID==CC_TARGET_PLATFORM)
    exit(0);
#endif
}

void ExitWin::resumeGame( CCObject *pSender )
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(HIDE_EXIT_WIN);
    removeFromParentAndCleanup(true);
}

