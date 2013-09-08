#ifndef _SHAKEBIRD_H_
#define _SHAKEBIRD_H_
#include "base/BaseSprite.h"
class ShakeBird:public BaseSprite
{
private:
    int shakeTimes;
public:
	int featherId;
    ShakeBird():shakeTimes(0) {};
    static ShakeBird *createShakeBird(const char *pszName);
    void shake(CCObject *pSender);
    void startShake();
};
#endif // !_SHAKEBIRD_H_
