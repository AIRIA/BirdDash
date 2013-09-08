#include "BaseSprite.h"

BaseSprite * BaseSprite::createSprite( const char *pszFileName,const char *soundName/*=NULL*/ )
{
    BaseSprite *baseSpr = new BaseSprite();
    if(baseSpr&&baseSpr->initWithSpriteFrameName(pszFileName))
    {
        baseSpr->autorelease();
        baseSpr->soundName = soundName;
    }
    return baseSpr;
}

void BaseSprite::setBeganTarget( CCObject* target,SEL_MenuHandler beganHandler )
{
    beganTarget = target;
    beganSelector = beganHandler;
}

void BaseSprite::setEndedTarget( CCObject* target,SEL_MenuHandler endedHandler )
{
    endedTarget = target;
    endedSelector = endedHandler;
}

void BaseSprite::setMovedTarget( CCObject* target,SEL_MenuHandler movedHandler )
{
    movedTarget = target;
    movedSelector = movedHandler;
}

void BaseSprite::setTouchEnabled( bool enabled )
{
    if (touchEnable!= enabled)
    {
        touchEnable = enabled;
        if (m_bRunning)
        {
            if (enabled)
            {
                CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,touchPriority,false);
            }
            else
            {
                CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
            }
        }
    }
}

void BaseSprite::setTouchPriority( int priority )
{
    //在设置的权重的时候 先移除掉事件代码 然后重新添加 来设置权重
    if(touchPriority!=priority)
    {
        touchPriority = priority;
        if(touchEnable)
        {
            setTouchEnabled(false);
            setTouchEnabled(true);
        }

    }
}

bool BaseSprite::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    if(isContainPoint(pTouch))
    {
        playEffect();
        if(beganTarget)
            (beganTarget->*beganSelector)(this);
        return true;
    }
    return false;
}

void BaseSprite::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    if(endedTarget)
        (endedTarget->*endedSelector)(this);
}

void BaseSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    if(movedTarget)
        (movedTarget->*movedSelector)(this);
}

bool BaseSprite::isContainPoint( CCTouch *pTouch )
{
    CCPoint arPoint = getAnchorPointInPoints();
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCSize spriteSize = getContentSize();
    CCRect spriteRect = CCRectMake(-arPoint.x,-arPoint.y,spriteSize.width,spriteSize.height);
    return spriteRect.containsPoint(point);
}

void BaseSprite::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

void BaseSprite::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,touchPriority,false);
    CCSprite::onEnter();
}

void BaseSprite::playEffect()
{
    if(soundName)
        SimpleAudioEngine::sharedEngine()->playEffect(this->soundName);
}

BaseSprite * BaseSprite::createFromFile( const char *pszFileName,const char *soundName/*=NULL*/ )
{
	BaseSprite *baseSpr = new BaseSprite();
	if(baseSpr&&baseSpr->initWithFile(pszFileName))
	{
		baseSpr->autorelease();
		baseSpr->soundName = soundName;
	}
	return baseSpr;
}

