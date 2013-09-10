#ifndef _BASEMENUSPRITE_H_
#define _BASEMENUSPRITE_H_

#include "common/CommonHeaders.h"

class BaseMenuSprite:public CCMenuItemSprite
{
private:
	CCObject *delegateTarget;
	SEL_MenuHandler delegateSelector;
	void delgateHandler(CCObject *pSender);
	const char *soundName;
public:
	static BaseMenuSprite *createMenuSprite(CCSprite *normal,CCSprite *pressed,CCSprite *disabled,CCObject *target, SEL_MenuHandler selecotr,const char *soundName=NULL);
};

#endif // !_BASEMENUSPRITE_H_
