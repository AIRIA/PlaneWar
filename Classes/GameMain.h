#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "common/PPHeaders.h"
#include "base/BaseScene.h"

class GameMain:public BaseScene
{
private:
    void __initBackground();
    void __scrollBackground();
    void __initLoadingAnimation();
    void __initCopyRight();
    CCSpriteBatchNode *m_pBgNode;
    float m_nBgHeight;
public:
    GameMain():m_nBgHeight(851){};
	virtual void loadAssets();
	virtual bool init();
	CREATE_FUNC(GameMain);
};

#endif // !_GAMEMAIN_H_
