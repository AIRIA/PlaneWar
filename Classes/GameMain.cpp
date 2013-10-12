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
    CCSprite *bg = CCSprite::createWithSpriteFrameName("background.png");
    bg->setPosition(VisibleRect::center());
    addChild(bg);
    return bRet;
}
