#include "AppDelegate.h"
#include "game/GameMain.h"
#include "SimpleAudioEngine.h"
#include "game/scenes/SplashScene.h"

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
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    pDirector->runWithScene(SplashScene::create());
#endif
#if(CC_TARGET_PLATFORM!=CC_PLATFORM_ANDROID)
	//pDirector->runWithScene(SplashScene::create());
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sounds/BGM/Main_bgm.mp3");
    pDirector->runWithScene(GameMain::create());
#endif
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
