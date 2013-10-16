#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "common/PPHeaders.h"
#include "base/BaseScene.h"
#include "components/Hero.h"
#include "components/BaseEnemy.h"

class GameMain:public BaseScene
{
private:
    CCSprite *m_pCopyRight;
    CCSprite *m_pLoading;
    CCLabelBMFont *m_pScore;
    int m_nScore;
    Hero *m_pHero;
	void __addAnimationFromArray(std::string *names,int length,int fps,const char *animateName);
    void __addAnimation(const char *prefix,int start,int end,int fps,const char *animationName);
    void __gameStart();
    void __initBackground();
    void __scrollBackground();
    void __initAnimation();
    void __initCopyRight();
    void __restart();
    void __createHero();
    void __gameOver();
    void __createEnemy(int type,float time,SEL_CallFunc selector);
    void __createEnemy1();
    void __createEnemy2();
    void __createEnemy3();
    void __initPauseBtn();
    void __pauseGame(CCObject *pSender);
    CCSpriteBatchNode *m_pBgNode;
    CCSpriteBatchNode *m_pBattleBatchNode;
    float m_nBgHeight;
public:
    GameMain():m_nBgHeight(851) {};
    virtual void loadAssets();
    virtual bool init();
    virtual void update(float);
    CREATE_FUNC(GameMain);
};

#endif // !_GAMEMAIN_H_
