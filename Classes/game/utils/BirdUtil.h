#ifndef _BIRDUTIL_H_
#define _BIRDUTIL_H_
#include "common/CommonHeaders.h"
#include "game/models/Bird.h"

class BirdUtil:public CCObject
{
public:
	static void initAnimate();
	static Bird *birds[PP_ROW][PP_COL];
	static void initBirds();
	static CCSpriteBatchNode *featherBatchNode;
	static CCPoint createRandomPoint(CCPoint pos,int range);
	static void createRandomFeather(CCNode *bird,const char *feather,int featherNum);
};

#endif // !_BIRDUTIL_H_
