#include "PPSprite.h"

PPSprite * PPSprite::createSprite( const char *pszFileName,const char *soundName/*=NULL*/ )
{
    PPSprite *pPPSprite = new PPSprite();
    if(pPPSprite&&pPPSprite->initWithSpriteFrameName(pszFileName))
    {
        pPPSprite->autorelease();
        pPPSprite->m_pSoundName = soundName;
    }
    return pPPSprite;
}

PPSprite * PPSprite::createFromFile( const char *pszFileName,const char *soundName/*=NULL*/ )
{
    PPSprite *pPPSprite = new PPSprite();
    if(pPPSprite&&pPPSprite->initWithFile(pszFileName))
    {
        pPPSprite->autorelease();
        pPPSprite->m_pSoundName = soundName;
    }
    return pPPSprite;
}

void PPSprite::onEnter()
{
    CCSprite::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_iTouchPriority,true);
}

void PPSprite::onExit()
{
    CCSprite::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}



bool PPSprite::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    if(_isContainPoint(pTouch))
    {
        _playEffect();
        if(m_pBeganTarget)
            (m_pBeganTarget->*beganSelector)(this);
        return true;
    }
    return false;
}

void PPSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    if(m_pMovedTarget)
        (m_pMovedTarget->*movedSelector)(this);
}

void PPSprite::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    if(m_pEndedTarget)
        (m_pEndedTarget->*endedSelector)(this);
}

void PPSprite::setBeganTarget( CCObject* target,SEL_MenuHandler beganHandler )
{
    this->m_pBeganTarget = target;
    this->beganSelector = beganHandler;
}

void PPSprite::setEndedTarget( CCObject* target,SEL_MenuHandler endedHandler )
{
    this->m_pEndedTarget = target;
    this->endedSelector = endedHandler;
}

void PPSprite::setMovedTarget( CCObject* target,SEL_MenuHandler movedHandler )
{
    this->m_pMovedTarget = target;
    this->movedSelector = movedHandler;
}

void PPSprite::setTouchEnabled( bool enabled )
{
    if (m_bTouchEnable!= enabled)
    {
        m_bTouchEnable = enabled;
        if (m_bRunning)
        {
            if (enabled)
            {
                CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_iTouchPriority,false);
            }
            else
            {
                CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
            }
        }
    }
}

void PPSprite::setTouchPriority( int priority )
{
    //在设置的权重的时候 先移除掉事件代码 然后重新添加 来设置权重
    if(m_iTouchPriority!=priority)
    {
        m_iTouchPriority = priority;
        if(m_bTouchEnable)
        {
            setTouchEnabled(false);
            setTouchEnabled(true);
        }

    }
}

bool PPSprite::_isContainPoint( CCTouch *pTouch )
{
    CCPoint arPoint = getAnchorPointInPoints();
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCSize spriteSize = getContentSize();
    CCRect spriteRect = CCRectMake(-arPoint.x,-arPoint.y,spriteSize.width,spriteSize.height);
    return spriteRect.containsPoint(point);
}

void PPSprite::_playEffect()
{
    if(m_pSoundName)
        SimpleAudioEngine::sharedEngine()->playEffect(this->m_pSoundName);
}
