#include "Bullet.h"
#define SPEED 500.0f
Bullet * Bullet::createBullet()
{
    Bullet *bullet = new Bullet();
    if(bullet&&bullet->initWithSpriteFrameName("bullet1.png"))
    {
        bullet->autorelease();
        bullet->__init();
    }
    return bullet;
}

void Bullet::__init()
{
    setAnchorPoint(ccp(0.5,1));
    scheduleUpdate();
    m_iWinSize = CCDirector::sharedDirector()->getWinSize();
}

void Bullet::__attack()
{
    float distance = m_iWinSize.height-getPositionY();
    float xPos = getPositionX();
    float time = distance/SPEED;
    CCMoveTo *moveAct = CCMoveTo::create(time,ccp(xPos,m_iWinSize.height+getContentSize().height));
    CCCallFunc *moveActCall = CCCallFunc::create(this,callfunc_selector(Bullet::removeFromParent));
    CCSequence *moveSeq = CCSequence::create(moveAct,moveActCall,NULL);
    runAction(moveSeq);
}

void Bullet::onEnter()
{
    CCSprite::onEnter();
    __attack();
	bullets->addObject(this);
	CCLog("bullets num %d",bullets->count());
}

void Bullet::onExit()
{
    CCSprite::onExit();
    bullets->fastRemoveObject(this);
	CCLog("bullets num %d",bullets->count());
}

