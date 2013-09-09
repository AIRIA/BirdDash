#include "SplashScene.h"
#include "game/GameMain.h"

bool SplashScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }
	CCSprite *splashImg = SPRITE(images/loading/splash.png);
	splashImg->setPosition(VisibleRect::center());
	addChild(splashImg);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sounds/BGM/Main_bgm.mp3");
	CCActionInterval *delayAct = CCDelayTime::create(3);
	CCCallFunc *enterGameHandler = CCCallFunc::create(this,callfunc_selector(SplashScene::enterGame));
	CCSequence *delaySeq = CCSequence::create(delayAct,enterGameHandler,NULL);
	runAction(delaySeq);
    return true;
}

void SplashScene::enterGame()
{
    CCDirector::sharedDirector()->replaceScene(GameMain::create());
}
