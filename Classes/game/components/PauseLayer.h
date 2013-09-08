#ifndef _PAUSELAYER_H_
#define _PAUSELAYER_H_

#include "common/CommonHeaders.h"

class PauseLayer:public CCLayer
{
private:
	CCLayerColor *bgLayer;
	void initBgLayer();
	void initMenu();
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
	virtual bool init();
	CREATE_FUNC(PauseLayer);
};

#endif // !_PAUSELAYER_H_
