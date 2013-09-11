#ifndef _BIRDLAYER_H_
#define _BIRDLAYER_H_

#include "common/CommonHeaders.h"

class BirdLayer:public CCLayer
{
public:
	void initBirds();
    virtual bool init();
    CREATE_FUNC(BirdLayer);
};

#endif // !_BIRDLAYER_H_
