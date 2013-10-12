#include "AppDelegate.h"
#include "GameMain.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    pEGLView->setDesignResolutionSize(480,852,kResolutionExactFit);
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/game_music.mp3");
    pDirector->runWithScene(GameMain::create());
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
