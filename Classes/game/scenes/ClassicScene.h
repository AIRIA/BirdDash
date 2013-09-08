#ifndef _CLASSICSCENE_H_
#define _CLASSICSCENE_H_

#include "base/BaseScene.h"

class ClassicScene:public BaseScene
{
private:
	void initBg();
protected:
	virtual void loadAsset();
public:
	virtual bool init();
	CREATE_FUNC(ClassicScene);
};

#endif // !_CLASSICSCENE_H_
