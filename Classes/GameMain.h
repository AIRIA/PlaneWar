#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "common/PPHeaders.h"
#include "base/BaseScene.h"
#include "components/Hero.h"
class GameMain:public BaseScene
{
private:
    CCSprite *m_pCopyRight;
    CCSprite *m_pLoading;
    Hero *m_pHero;
    void __gameStart();
    void __initBackground();
    void __scrollBackground();
    void __initLoadingAnimation();
    void __initCopyRight();
    void __restart();
    void __createHero();
    void __gameOver();
    CCSpriteBatchNode *m_pBgNode;
    CCSpriteBatchNode *m_pBattleBatchNode;
    float m_nBgHeight;
public:
    GameMain():m_nBgHeight(851) {};
    virtual void loadAssets();
    virtual bool init();
    CREATE_FUNC(GameMain);
};

#endif // !_GAMEMAIN_H_
