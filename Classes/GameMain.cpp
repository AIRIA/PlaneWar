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
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
    __initBackground();
    
    return bRet;
}

void GameMain::__initBackground()
{
    m_pBgNode = CCSpriteBatchNode::createWithTexture(m_pFrameCache->spriteFrameByName("background.png")->getTexture());
    m_pBgNode->setPosition(ccp(m_iWinSize.width/2,-120));
    CCSprite *bg1 = CCSprite::createWithSpriteFrameName("background.png");
    CCSprite *bg2 = CCSprite::createWithSpriteFrameName("background.png");
    bg1->setAnchorPoint(ccp(0.5,0));
    bg2->setAnchorPoint(ccp(0.5,0));
    bg1->setPosition(ccp(0,0));
    bg2->setPosition(ccp(0,851));
    m_pBgNode->addChild(bg1);
    m_pBgNode->addChild(bg2);
    addChild(m_pBgNode);
    __scrollBackground();
}

void GameMain::__scrollBackground()
{
    if(m_pBgNode->getPositionY()!=0)
    {
        CCLog("循环一次完成");
        m_pBgNode->setPositionY(0);
    }
    CCActionInterval *moveDown = CCMoveTo::create(10, ccp(m_iWinSize.width/2, -851));
    CCCallFunc *resetHandler = CCCallFunc::create(this, callfunc_selector(GameMain::__scrollBackground));
    CCSequence *moveSeq = CCSequence::create(moveDown,resetHandler,NULL);
    m_pBgNode->runAction(moveSeq);
}
