#ifndef _PAUSELAYER_H_
#define _PAUSELAYER_H_

#include "common/CommonHeaders.h"

class PauseLayer:public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(PauseLayer);
};

#endif // !_PAUSELAYER_H_
