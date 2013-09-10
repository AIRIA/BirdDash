#ifndef _MASKLAYER_H_
#define _MASKLAYER_H_

#include "common/CommonHeaders.h"

class MaskLayer:public CCLayerColor
{
public:
    virtual bool init();
    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    CREATE_FUNC(MaskLayer);
};

#endif // !_MASKLAYER_H_
