#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_

#include "common/PPHeaders.h"

class BaseScene:public CCScene
{
protected:
    CCSpriteFrameCache *m_pFrameCache;
    CCSize m_iWinSize;
public:
    virtual void loadAssets()=0;
    virtual bool init();
};

#endif // !_BASE_SCENE_H_
