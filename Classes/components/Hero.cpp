#include "Hero.h"

Hero * Hero::createHero()
{
    Hero *hero = new Hero();
    if(hero&&hero->initWithSpriteFrameName("hero1.png"))
    {
        hero->autorelease();
        hero->m_iWinSize = CCDirector::sharedDirector()->getWinSize();
    }
    return hero;
}

void Hero::onEnter()
{
    PPSprite::onEnter();
    __attack();
    runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("hero"))));
}

void Hero::__attack()
{
	//SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
    CCDelayTime *delay = CCDelayTime::create(0.1f);
    float posY = getPositionY()+getContentSize().height/2;
    if(posY<m_iWinSize.height)
    {
        Bullet *bullet = Bullet::createBullet();
        bullet->setPosition(ccp(getPosition().x,getPosition().y+getContentSize().height/2-5));
        bullet->setZOrder(-1);
        getParent()->addChild(bullet);
    }
    CCCallFunc *callback = CCCallFunc::create(this,callfunc_selector(Hero::__attack));
    CCSequence *seq = CCSequence::create(delay,callback,NULL);
    runAction(seq);
}

void Hero::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint currentPoint = pTouch->getLocation();
    setPosition(currentPoint);
}
