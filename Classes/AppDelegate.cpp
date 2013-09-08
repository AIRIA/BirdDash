#include "AppDelegate.h"
#include "game/GameMain.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    pEGLView->setDesignResolutionSize(640,960,kResolutionExactFit);
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    CCScene *pScene = GameMain::create();
    pDirector->runWithScene(pScene);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sounds/BGM/Main_bgm.mp3");
    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}


void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
