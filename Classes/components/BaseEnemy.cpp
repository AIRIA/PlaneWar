﻿#include "BaseEnemy.h"

void BaseEnemy::onEnter()
{
    CCSprite::onEnter();
    __attack();
}

void BaseEnemy::__attack()
{
    float distance = m_iWinSize.height+getContentSize().height;
    float time = distance/speed;
    CCActionInterval *moveTo = CCMoveBy::create(time,ccp(0,-distance));
    CCCallFunc *moveCall = CCCallFunc::create(this,callfunc_selector(BaseEnemy::removeFromParent));
    CCSequence *moveSeq = CCSequence::create(moveTo,moveCall,NULL);
    runAction(moveSeq);
}

void BaseEnemy::__init()
{
    setAnchorPoint(ccp(0.5,0));
    m_iWinSize = CCDirector::sharedDirector()->getWinSize();
    __getRandomPosition();
}

void BaseEnemy::setType( int val )
{
    m_nType = val;
    switch (m_nType)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }
}

BaseEnemy * BaseEnemy::createEnemy( int type )
{
    BaseEnemy *be = new BaseEnemy();
    be->speed = 200/type+rand()%100;
    CCLog("speed:%f",be->speed);
    const char *enemyName = CCString::createWithFormat("enemy%d.png",type)->getCString();
    if(type==3)
    {
        enemyName = "enemy3_n1.png";
    }

    if(be&&be->initWithSpriteFrameName(enemyName))
    {
        be->autorelease();
        be->__init();
    }
    return be;
}

void BaseEnemy::__getRandomPosition()
{
    CCSize size = getContentSize();
    float left = size.width/2;
    float range = m_iWinSize.width-size.width;
    int offsetx = rand()%(int)(range);
    setPosition(ccp(offsetx+left,VisibleRect::top().y));
}
