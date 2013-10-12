#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "common/PPHeaders.h"
#include "base/BaseScene.h"

class GameMain:public BaseScene
{
public:
	virtual void loadAssets();
	virtual bool init();
	CREATE_FUNC(GameMain);
};

#endif // !_GAMEMAIN_H_
