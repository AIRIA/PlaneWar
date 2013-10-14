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
    srand(time(NULL));
    m_pBgNode = CCSpriteBatchNode::createWithTexture(m_pFrameCache->spriteFrameByName("background.png")->getTexture());
    addChild(m_pBgNode);
    m_pBattleBatchNode = CCSpriteBatchNode::createWithTexture(m_pFrameCache->spriteFrameByName("hero1.png")->getTexture());
    addChild(m_pBattleBatchNode);

    __initAnimation();
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

inline void GameMain::__initAnimation()
{
    __addAnimation("game_loading%d.png",1,4,2,"loading");
    __addAnimation("enemy1_down%d.png",1,4,8,"enemy1_down");
    __addAnimation("enemy2_down%d.png",1,4,8,"enemy2_down");
    __addAnimation("enemy3_down%d.png",1,6,8,"enemy3_down");
    __addAnimation("hero_blowup_n%d.png",1,4,8,"hero_down");
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
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
    __scrollBackground();
    m_pBgNode->removeChild(m_pLoading,true);
    m_pBgNode->removeChild(m_pCopyRight,true);
    __createHero();
    __createEnemy1();
    __createEnemy2();
    __createEnemy3();
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

void GameMain::__addAnimation( const char *prefix,int start,int end,int fps,const char *animationName )
{
    CCArray *spriteFrames = CCArray::createWithCapacity(end);
    for(int i=start; i<=end; i++)
    {
        const char *pszName = CCString::createWithFormat(prefix,i)->getCString();
        CCSpriteFrame *spriteFrame = m_pFrameCache->spriteFrameByName(pszName);
        spriteFrames->addObject(spriteFrame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(spriteFrames,1.0/fps);
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation,animationName);
}

void GameMain::__createEnemy1()
{
    float time = (rand()%10)/10.0f+1.0f;
    BaseEnemy *enemy = BaseEnemy::createEnemy(1);
    m_pBattleBatchNode->addChild(enemy);
    CCDelayTime *delay = CCDelayTime::create(time);
    CCCallFunc *delayCall = CCCallFunc::create(this,callfunc_selector(GameMain::__createEnemy1));
    CCSequence *seq = CCSequence::create(delay,delayCall,NULL);
    runAction(seq);
}
void GameMain::__createEnemy2()
{
    float time = rand()%3+2;
    BaseEnemy *enemy = BaseEnemy::createEnemy(2);
    m_pBattleBatchNode->addChild(enemy);
    CCDelayTime *delay = CCDelayTime::create(time);
    CCCallFunc *delayCall = CCCallFunc::create(this,callfunc_selector(GameMain::__createEnemy2));
    CCSequence *seq = CCSequence::create(delay,delayCall,NULL);
    runAction(seq);
}
void GameMain::__createEnemy3()
{
    float time = rand()%3+4;
    BaseEnemy *enemy = BaseEnemy::createEnemy(3);
    m_pBattleBatchNode->addChild(enemy);
    CCDelayTime *delay = CCDelayTime::create(time);
    CCCallFunc *delayCall = CCCallFunc::create(this,callfunc_selector(GameMain::__createEnemy3));
    CCSequence *seq = CCSequence::create(delay,delayCall,NULL);
    runAction(seq);
}
