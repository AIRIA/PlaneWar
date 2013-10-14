#ifndef _PPSPRITE_H_
#define _PPSPRITE_H_

#include "common/PPHeaders.h"

class PPSprite:public CCSprite,public CCTouchDelegate
{
private:
    const char *m_pSoundName;
protected:
    CCObject *m_pBeganTarget;
    SEL_MenuHandler beganSelector;
    CCObject *m_pEndedTarget;
    SEL_MenuHandler endedSelector;
    CCObject *m_pMovedTarget;
    SEL_MenuHandler movedSelector;
    int m_iTouchPriority;
    bool m_bTouchEnable;
    void _playEffect();
    /* 触摸的点是否在节点的响应区域内 */
    bool _isContainPoint(CCTouch *pTouch);
public:
    //************************************
    // Method:    PPSprite
    // FullName:  PPSprite::PPSprite
    // Access:    public
    // Returns:
    // Qualifier: :m_pSoundName(NULL), m_pBeganTarget(NULL), beganSelector(NULL), m_pEndedTarget(NULL), endedSelector(NULL), m_pMovedTarget(NULL), movedSelector(NULL), m_iTouchPriority(0)
    //************************************
    PPSprite():m_pSoundName(NULL),
        m_pBeganTarget(NULL),
        beganSelector(NULL),
        m_pEndedTarget(NULL),
        endedSelector(NULL),
        m_pMovedTarget(NULL),
        movedSelector(NULL),
        m_iTouchPriority(0) {};
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);


    //************************************
    // Method:    createSprite
    // FullName:  PPSprite::createSprite
    // Access:    public static
    // Returns:   PPSprite *
    // Qualifier: 根据纹理的名字创建精灵
    // Parameter: const char * pszFileName 精灵名字
    // Parameter: const char * soundName 在触摸的时候播放的音效
    //************************************
    static PPSprite *createSprite(const char *pszFileName,const char *soundName=NULL);

    //************************************
    // Method:    createFromFile
    // FullName:  PPSprite::createFromFile
    // Access:    public static
    // Returns:   PPSprite *
    // Qualifier:
    // Parameter: const char * pszFileName
    // Parameter: const char * soundName
    //************************************
    static PPSprite *createFromFile(const char *pszFileName,const char *soundName=NULL);

    void setBeganTarget(CCObject* target,SEL_MenuHandler beganHandler);
    //************************************
    // Method:    setEndedTarget
    // FullName:  PPSprite::setEndedTarget
    // Access:    public
    // Returns:   void
    // Qualifier: 移动的时候触发
    // Parameter: CCObject * target
    // Parameter: SEL_MenuHandler endedHandler
    //************************************
    void setEndedTarget(CCObject* target,SEL_MenuHandler endedHandler);
    //************************************
    // Method:    setMovedTarget
    // FullName:  PPSprite::setMovedTarget
    // Access:    public
    // Returns:   void
    // Qualifier: 触摸结束的时候触发
    // Parameter: CCObject * target
    // Parameter: SEL_MenuHandler movedHandler
    //************************************
    void setMovedTarget(CCObject* target,SEL_MenuHandler movedHandler);
    //************************************
    // Method:    setTouchEnabled
    // FullName:  PPSprite::setTouchEnabled
    // Access:    public
    // Returns:   void
    // Qualifier: 设置是否可以响应触摸事件
    // Parameter: bool value
    //************************************
    void setTouchEnabled(bool value);
    //************************************
    // Method:    setTouchPriority
    // FullName:  PPSprite::setTouchPriority
    // Access:    public
    // Returns:   void
    // Qualifier: 设置事件权重
    // Parameter: int value
    //************************************
    void setTouchPriority(int value);
};

#endif // !_PPSPRITE_H_
