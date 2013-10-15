#ifndef _BULLET_H_
#define _BULLET_H_

#include "common/PPHeaders.h"

class Bullet:public CCSprite
{
private:
    CCSize m_iWinSize;
    void __attack();
    virtual void __init();
    bool m_bIsLock;
public:
    void setLock(bool val){
        m_bIsLock = val;
    };
    bool getLock() const{
        return m_bIsLock;
    };
    virtual void onEnter();
    virtual void onExit();
    static Bullet *createBullet();
};

#endif // !_BULLET_H_
