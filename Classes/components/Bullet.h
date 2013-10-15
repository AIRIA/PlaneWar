#ifndef _BULLET_H_
#define _BULLET_H_

#include "common/PPHeaders.h"

class Bullet:public CCSprite
{
private:
    CCSize m_iWinSize;
    void __attack();
    virtual void __init();
public:
    virtual void onEnter();
    virtual void onExit();
    static Bullet *createBullet();
};

#endif // !_BULLET_H_
