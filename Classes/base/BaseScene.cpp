#include "BaseScene.h"

bool BaseScene::init()
{
    if(!CCScene::init())
    {
        return false;
    }
    m_pFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->purgeCachedData();
    m_iWinSize = pDirector->getWinSize();
    loadAssets();
    return true;
}
