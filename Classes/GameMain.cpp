#include "GameMain.h"

void GameMain::loadAssets()
{
    m_pFrameCache->addSpriteFramesWithFile("shoot_bg.plist");
    m_pFrameCache->addSpriteFramesWithFile("shoot.plist");
}

bool GameMain::init()
{
    bool bRet = true;
    if(!BaseScene::init())
    {
        bRet = false;
    }
    m_pBgNode = CCSpriteBatchNode::createWithTexture(m_pFrameCache->spriteFrameByName("background.png")->getTexture());
    addChild(m_pBgNode);
    m_pBattleBatchNode = CCSpriteBatchNode::createWithTexture(m_pFrameCache->spriteFrameByName("hero1.png")->getTexture());
    addChild(m_pBattleBatchNode);
    //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
    __initLoadingAnimation();
    __initBackground();
    __initCopyRight();
    return bRet;
}

inline void GameMain::__initBackground()
{
    CCSprite *bg1 = CCSprite::createWithSpriteFrameName("background.png");
    CCSprite *bg2 = CCSprite::createWithSpriteFrameName("background.png");
    m_pBgNode->getTexture()->setAliasTexParameters();
    bg1->setAnchorPoint(ccp(0,0));
    bg2->setAnchorPoint(ccp(0,0));
    bg1->setPosition(ccp(0,0));
    bg2->setPosition(ccp(0,m_nBgHeight-3));
    m_pBgNode->addChild(bg1);
    m_pBgNode->addChild(bg2);
}

void GameMain::__scrollBackground()
{
    m_pBgNode->setPositionY(0);
    CCActionInterval *moveDown = CCMoveTo::create(5, ccp(0, -m_nBgHeight));
    CCCallFunc *resetHandler = CCCallFunc::create(this, callfunc_selector(GameMain::__scrollBackground));
    CCSequence *moveSeq = CCSequence::create(moveDown,resetHandler,NULL);
    m_pBgNode->runAction(moveSeq);
}

inline void GameMain::__initLoadingAnimation()
{
    CCArray *loadingFrames = CCArray::createWithCapacity(4);
    for(int i=1; i<5; i++)
    {
        const char *pszName = CCString::createWithFormat("game_loading%d.png",i)->getCString();
        CCSpriteFrame *loadingFrame = m_pFrameCache->spriteFrameByName(pszName);
        loadingFrames->addObject(loadingFrame);
    }
    CCAnimation *loadingAnimation = CCAnimation::createWithSpriteFrames(loadingFrames,0.5f);
    CCAnimationCache *animationCache = CCAnimationCache::sharedAnimationCache();
    animationCache->addAnimation(loadingAnimation, "loading");
}

inline void GameMain::__initCopyRight()
{
    m_pCopyRight = CCSprite::createWithSpriteFrameName("shoot_copyright.png");
    m_pCopyRight->setPosition(ccp(VisibleRect::center().x,VisibleRect::top().y-200));
    m_pBgNode->addChild(m_pCopyRight);
    m_pLoading = CCSprite::createWithSpriteFrameName("game_loading1.png");
    m_pLoading->setPosition(VisibleRect::center());
    CCAnimate *loadingAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("loading"));
    CCCallFunc *loadingCallback = CCCallFunc::create(this,callfunc_selector(GameMain::__gameStart));
    CCRepeat *repeate = CCRepeat::create(loadingAnimate,1);
    CCSequence *loadingSeq = CCSequence::create(repeate,loadingCallback,NULL);
    m_pLoading->runAction(loadingSeq);
    m_pBgNode->addChild(m_pLoading);
}

void GameMain::__gameStart()
{
    __scrollBackground();
    m_pBgNode->removeChild(m_pLoading,true);
    m_pBgNode->removeChild(m_pCopyRight,true);
    __createHero();
}

void GameMain::__restart()
{
    __initCopyRight();
}

void GameMain::__createHero()
{
    m_pHero = Hero::createHero();
    m_pHero->setPosition(ccp(m_iWinSize.width/2,(m_pHero->getContentSize()).height/2));
    m_pBattleBatchNode->addChild(m_pHero);
}

void GameMain::__gameOver()
{

}
