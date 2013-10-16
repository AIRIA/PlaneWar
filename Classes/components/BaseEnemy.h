#ifndef _BASEENEMY_H_
#define _BASEENEMY_H_

#include "common/PPHeaders.h"

class BaseEnemy:public CCSprite
{
private:
    void __attack();
    CCSize m_iWinSize;
    void __init();
	void __getRandomPosition();
    int m_nType;
public:
    int m_nHP;
	int state;
    void setType(int val);
	int getType() const{
		return m_nType;
	};
	void runBaseAction();
	void stopBaseAction();
	void destroy();
    float speed;
    virtual void onEnter();
	virtual void onExit();
	BaseEnemy();
    static BaseEnemy *createEnemy(int type);
};

#endif // !_BASEENEMY_H_
