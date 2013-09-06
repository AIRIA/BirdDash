#include "BaseScene.h"

bool BaseScene::init()
{
    bool res = false;
    do
    {
        CC_BREAK_IF(!CCScene::init());
        CCDirector::sharedDirector()->purgeCachedData();
        CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
        frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
        frameCache->removeUnusedSpriteFrames();
		loadAsset();
        res = true;
    }
    while (0);
    return res;
}