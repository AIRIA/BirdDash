#ifndef _SPLASHSCENE_H_
#define _SPLASHSCENE_H_

#include "common/CommonHeaders.h"
#include "base/BaseScene.h"

class SplashScene:public BaseScene
{
public:
	void enterGame();
	virtual bool init();
	CREATE_FUNC(SplashScene);
};

#endif // !_SPLASHSCENE_H_
