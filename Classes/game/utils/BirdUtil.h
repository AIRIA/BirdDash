#ifndef _BIRDUTIL_H_
#define _BIRDUTIL_H_
#include "common/CommonHeaders.h"
#include "game/models/Bird.h"

class DashInfo
{
public:
    CCArray *neighbors;
    std::set<int> cols;
    DashInfo()
    {
        neighbors = CCArray::create();
        neighbors->retain();
    };
};

class BirdUtil:public CCObject
{
private:
    static BirdUtil *_instance;
public:
    static std::set<int> cols;
    /* 更新制定列中小鸟的位置 */
    static void updateColPosition(int col,int row=0);
    void removeFeather(CCNode *node);
    static BirdUtil *getInstance();
    static void initAnimate();
    static Bird *birds[PP_ROW][PP_COL];
    static void initBirds();
    static CCSpriteBatchNode *featherBatchNode;
    static CCPoint createRandomPoint(CCPoint pos,int range);
    static void createRandomFeather(CCNode *bird,const char *feather,int featherNum);
    /* 检测所有可以消除的 */
    static void checkAlltoDrop();
    /* 设置所有的都到没有检测的状态 */
    static void resetAlltoUncheck();
};

#endif // !_BIRDUTIL_H_
