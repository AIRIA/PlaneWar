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
   
    //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
    __initLoadingAnimation();
    __initBackground();
    __initCopyRight();
    return bRet;
}

inline void GameMain::__initBackground()
{
    m_pBgNode = CCSpriteBatchNode::createWithTexture(m_pFrameCache->spriteFrameByName("background.png")->getTexture());
    m_pBgNode->setPosition(ccp(m_iWinSize.width/2,0));
    CCSprite *bg1 = CCSprite::createWithSpriteFrameName("background.png");
    CCSprite *bg2 = CCSprite::createWithSpriteFrameName("background.png");
    m_pBgNode->getTexture()->setAliasTexParameters();
    bg1->setAnchorPoint(ccp(0.5,0));
    bg2->setAnchorPoint(ccp(0.5,0));
    bg1->setPosition(ccp(0,0));
    bg2->setPosition(ccp(0,m_nBgHeight-3));
    m_pBgNode->addChild(bg1);
    m_pBgNode->addChild(bg2);
    addChild(m_pBgNode);
}

void GameMain::__scrollBackground()
{
    m_pBgNode->setPositionY(0);
    CCActionInterval *moveDown = CCMoveTo::create(5, ccp(m_iWinSize.width/2, -m_nBgHeight));
    CCCallFunc *resetHandler = CCCallFunc::create(this, callfunc_selector(GameMain::__scrollBackground));
    CCSequence *moveSeq = CCSequence::create(moveDown,resetHandler,NULL);
    m_pBgNode->runAction(moveSeq);
}

inline void GameMain::__initLoadingAnimation()
{
    CCArray *loadingFrames = CCArray::createWithCapacity(4);
    for(int i=1;i<5;i++)
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
    CCSprite *copyRight = CCSprite::createWithSpriteFrameName("shoot_copyright.png");
    copyRight->setPosition(ccp(VisibleRect::center().x,VisibleRect::top().y-200));
    addChild(copyRight);
    CCSprite *loading = CCSprite::createWithSpriteFrameName("game_loading1.png");
    loading->setPosition(VisibleRect::center());
    CCAnimate *loadingAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("loading"));
    loading->runAction(CCRepeatForever::create(loadingAnimate));
    addChild(loading);
}
