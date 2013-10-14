#include "Hero.h"

Hero * Hero::createHero()
{
    Hero *hero = new Hero();
    if(hero&&hero->initWithSpriteFrameName("hero1.png"))
    {
        hero->autorelease();
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
    CCDelayTime *delay = CCDelayTime::create(0.1f);
    Bullet *bullet = Bullet::createBullet();
    bullet->setPosition(ccp(getPosition().x,getPosition().y+getContentSize().height/2-5));
    CCCallFunc *callback = CCCallFunc::create(this,callfunc_selector(Hero::__attack));
    CCSequence *seq = CCSequence::create(delay,callback,NULL);
	bullet->setZOrder(-1);
    getParent()->addChild(bullet);
    runAction(seq);
}

void Hero::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint currentPoint = pTouch->getLocation();
    setPosition(currentPoint);
}
