#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "common/CommonHeaders.h"
#include "base/BaseScene.h"

class GameMain:public BaseScene
{
private:
	void jumptoSetting(CCObject *pSender);
	void jumptoStageClassic(CCObject *pSender);
	void setBird(const char *bird,CCPoint pos,CCPoint upDown,int featherId,float sec);
	void moveTitle(CCNode *node);
	void playShowBirdSound(CCNode *node,void *param);
	CCSpriteBatchNode *birdBatchNode;
protected:
	virtual void loadAsset();
public:
	void setSetting();
	void addBirds();
	void setMainbg();
    virtual bool init();
    CREATE_FUNC(GameMain);
	virtual void keyBackClicked();
};

#endif // !_GAMEMAIN_H_
