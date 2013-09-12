#ifndef _BIRDUTIL_H_
#define _BIRDUTIL_H_
#include "common/CommonHeaders.h"
#include "game/models/Bird.h"

class BirdUtil:public CCObject
{
private:
    static BirdUtil *_instance;
public:
    /* 更新制定列中小鸟的位置 */
    static void updateColPosition(int col);
    void removeFeather(CCNode *node);
    static BirdUtil *getInstance();
    static void initAnimate();
    static Bird *birds[PP_ROW][PP_COL];
    static void initBirds();
    static CCSpriteBatchNode *featherBatchNode;
    static CCPoint createRandomPoint(CCPoint pos,int range);
    static void createRandomFeather(CCNode *bird,const char *feather,int featherNum);
};

#endif // !_BIRDUTIL_H_
