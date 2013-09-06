#ifndef _BASESPRITE_H_
#define _BASESPRITE_H_

#include "common/CommonHeaders.h"

class BaseSprite:public CCSprite,public CCTouchDelegate
{
private:
    /* 触摸的点是否在节点的响应区域内 */
    bool isContainPoint(CCTouch *pTouch);
    const char *soundName;
protected:
    CCObject *beganTarget;
    SEL_MenuHandler beganSelector;
    CCObject *endedTarget;
    SEL_MenuHandler endedSelector;
    CCObject *movedTarget;
    SEL_MenuHandler movedSelector;
    int touchPriority;
    bool touchEnable;
    void playEffect();
public:
    BaseSprite():soundName(NULL),beganTarget(NULL),beganSelector(NULL),endedTarget(NULL),endedSelector(NULL),movedTarget(NULL),movedSelector(NULL) {};
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);


    /* 根据纹理的名字创建精灵
     * @param pszFileName 精灵名字
     * @param soundName 在触摸的时候播放的音效
     */
    static BaseSprite *createSprite(const char *pszFileName,const char *soundName=NULL);
    /* 开始触摸的时候触发 */
    void setBeganTarget(CCObject* target,SEL_MenuHandler beganHandler);
    /* 移动的时候触发 */
    void setEndedTarget(CCObject* target,SEL_MenuHandler endedHandler);
    /* 触摸结束的时候触发 */
    void setMovedTarget(CCObject* target,SEL_MenuHandler movedHandler);
    /* 设置是否可以响应触摸事件 */
    void setTouchEnabled(bool value);
    /* 设置事件权重 */
    void setTouchPriority(int value);

};


#endif // !_BASESPRITE_H_
