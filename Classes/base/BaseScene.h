#ifndef _BASESCENE_H_
#define _BASESCENE_H_

#include "common/CommonHeaders.h"

class BaseScene:public CCScene,public CCKeypadDelegate
{
protected:
    /* 此处加载该场景所需要的资源 */
    virtual void loadAsset() {};
    CCSize winSize;
	bool isShowExit;
public:
    CCSpriteFrameCache *frameCache;
    BaseScene():frameCache(NULL),isShowExit(false)
    {
        winSize = CCDirector::sharedDirector()->getWinSize();
    };
    virtual bool init();
    CREATE_FUNC(BaseScene);
};

#endif // !_BASESCENE_H_
