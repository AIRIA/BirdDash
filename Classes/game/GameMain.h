#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "common/CommonHeaders.h"
#include "base/BaseScene.h"

class GameMain:public BaseScene
{
private:
	void menuBgComplete();
	void jumptoSetting(CCObject *pSender);
	void jumptoStageClassic(CCObject *pSender);
	void setBird(const char *bird,CCPoint pos,CCPoint upDown,int featherId);
	CCSpriteBatchNode *birdBatchNode;
protected:
	virtual void loadAsset();
public:
	void setSetting();
	void addBirds();
	void setMainbg();
    virtual bool init();
    CREATE_FUNC(GameMain);
};

#endif // !_GAMEMAIN_H_
