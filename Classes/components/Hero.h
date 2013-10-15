#ifndef _HERO_H_
#define _HERO_H_

#include "base/PPSprite.h"
#include "Bullet.h"

class Hero:public PPSprite
{
private:
	CCSize m_iWinSize;
    void __attack();
	void __init();
public:
    virtual void onEnter();
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    static Hero *createHero();
};

#endif // !_HERO_H_
