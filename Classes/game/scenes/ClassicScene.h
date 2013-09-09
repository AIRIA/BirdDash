#ifndef _CLASSICSCENE_H_
#define _CLASSICSCENE_H_

#include "base/BaseScene.h"

class ClassicScene:public BaseScene
{
private:
	void initBg();
	void pauseGame(CCObject *pSender);
protected:
	virtual void loadAsset();
public:
	virtual bool init();
	CREATE_FUNC(ClassicScene);
	virtual void keyBackClicked();
};

#endif // !_CLASSICSCENE_H_
