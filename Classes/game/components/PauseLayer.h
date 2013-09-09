#ifndef _PAUSELAYER_H_
#define _PAUSELAYER_H_

#include "common/CommonHeaders.h"

class PauseLayer:public CCLayer
{
private:
	CCLayerColor *bgLayer;
	CCNode *menuNode;
	CCMenu *gameMenu;
	void initBgLayer();
	void initMenu();
	void resumeHandler(CCObject *pSender);
	void quitHandler(CCObject *pSender);
	void destroy();
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void showExit(CCObject* pSender);
	CREATE_FUNC(PauseLayer);
};

#endif // !_PAUSELAYER_H_
