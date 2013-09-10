#include "BaseMenuSprite.h"

BaseMenuSprite * BaseMenuSprite::createMenuSprite( CCSprite *normal,CCSprite *pressed,CCSprite *disabled,CCObject *target, SEL_MenuHandler selecotr ,const char *soundName/*=NULL*/)
{
    BaseMenuSprite *bms = new BaseMenuSprite();
    bms->delegateTarget = target;
    bms->delegateSelector = selecotr;
    bms->soundName = soundName;
    if(bms&&bms->initWithNormalSprite(normal,pressed,disabled,bms,menu_selector(BaseMenuSprite::delgateHandler)))
    {
        bms->autorelease();
        return bms;
    }
    CC_SAFE_DELETE(bms);
    return NULL;
}

void BaseMenuSprite::delgateHandler( CCObject *pSender )
{
    if(soundName)
        SimpleAudioEngine::sharedEngine()->playEffect(soundName);
    if(delegateTarget)
        (delegateTarget->*delegateSelector)(pSender);
}
