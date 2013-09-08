#include "SettingScene.h"
#include "base/BaseSprite.h"
#include "game/GameMain.h"

bool SettingScene::init()
{
    bool res = false;
    do
    {
        CC_BREAK_IF(!BaseScene::init());
        //背景
        CCSprite *settingBg = SPRITE(images/options/option_bg_RETINA.png);
        settingBg->setPosition(VisibleRect::center());
        addChild(settingBg);
        //title
        CCSprite *title = SPRITE_FRAME(option_soundandvibration_china@2x.png);
        title->setPosition(ccp(VisibleRect::center().x,VisibleRect::top().y-120));
        addChild(title);
        //credits
        CCSprite *credits = SPRITE_FRAME(option_credit_china@2x.png);
        credits->setPosition(ccp(VisibleRect::center().x,VisibleRect::top().y-530));
        addChild(credits);
        res = true;
        //home
        BaseSprite *homeSpr = BaseSprite::createSprite("scores_home@2x.png");
        homeSpr->setPosition(ccp(VisibleRect::right().x-68,68));
        homeSpr->setEndedTarget(this,menu_selector(SettingScene::backToHome));
        addChild(homeSpr);
        //声音
        CCSprite *soundIcon = SPRITE_FRAME(option_icon_sound@2x.png);
        CCSprite *soundText = SPRITE_FRAME(option_sound_china@2x.png);
        soundIcon->setPosition(ccp(100,VisibleRect::top().y-200));
        soundText->setPosition(ccp(150,VisibleRect::top().y-200));
        addChild(soundIcon);
        addChild(soundText);
        //声音开关
        CCMenuItemSprite *soundOn = CCMenuItemSprite::create(SPRITE_FRAME(option_button_on@2x.png),SPRITE_FRAME(option_button_on@2x.png));
        CCMenuItemSprite *soundOff = CCMenuItemSprite::create(SPRITE_FRAME(option_button_off@2x.png),SPRITE_FRAME(option_button_off@2x.png));
        CCMenuItemToggle *sound = CCMenuItemToggle::createWithTarget(this,menu_selector(SettingScene::soundHandler),soundOn,soundOff,NULL);
        CCMenu *soundMenu = CCMenu::create(sound,NULL);
        soundMenu->alignItemsVertically();
        soundMenu->setPosition(ccp(500,VisibleRect::top().y-200));
        addChild(soundMenu);
    }
    while (0);
    return res;
}

void SettingScene::loadAsset()
{
    frameCache->addSpriteFramesWithFile("images/options/option_CN_RETINA.plist");
    frameCache->addSpriteFramesWithFile("images/options/option_RETINA.plist");
}

void SettingScene::backToHome( CCObject *pSender )
{
    CCDirector::sharedDirector()->replaceScene(GameMain::create());
}

void SettingScene::soundHandler( CCObject *pSender )
{
    CCMenuItemToggle *sound = (CCMenuItemToggle*)pSender;
    if(sound->getSelectedIndex()==0)
    {
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    else
    {
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
}

