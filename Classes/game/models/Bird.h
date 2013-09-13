#ifndef _BIRD_H_
#define _BIRD_H_

#include "common/CommonHeaders.h"
#include "base/BaseSprite.h"

class Bird:public BaseSprite
{
public:
    /* 是不是已经遍历过了 */
    bool isChecked;
    int row;
    int col;
    int type;
    int state;
    bool dragable;
    bool isFlying;
    Bird():isChecked(false),dragable(false),isFlying(false){};
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    static Bird *createBird(int type);
    virtual void onEnter();
    void eyeclose();
    void reorderSelf();
    /* 缩动身体后 随机掉落羽毛 */
    void shake();
    /* 飘落羽毛 */
    void featherFly();
    /*是否可以拖拽*/
    bool isDragable();
    /* 在拖动的时候更新在数组中的位置 */
    void updatePosition(CCTouch *pTouch);
    /* 获取右边和上边的 */
    void *getNeighbors(CCArray *neighbor);
};

#endif // !_BIRD_H_
