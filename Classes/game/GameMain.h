#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "common/CommonHeaders.h"
#include "base/BaseScene.h"

class GameMain:public BaseScene
{
private:
	void setBird(const char *bird,CCPoint pos,CCPoint upDown);
	CCSpriteBatchNode *birdBatchNode;
protected:
	virtual void loadAsset();
public:
	void addBirds();
	void setMainbg();
    virtual bool init();
    CREATE_FUNC(GameMain);
};

#endif // !_GAMEMAIN_H_
