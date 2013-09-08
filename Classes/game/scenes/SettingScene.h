#ifndef _SETTINGSCENE_H_
#define _SETTINGSCENE_H_

#include "base/BaseScene.h"

class SettingScene:public BaseScene
{
public:
	virtual void soundHandler(CCObject *pSender);
	virtual void backToHome(CCObject *pSender);
	virtual void loadAsset();
	virtual bool init();
	CREATE_FUNC(SettingScene);
};

#endif // !_SETTINGSCENE_H_
