#include "GameMain.h"

void GameMain::loadAssets()
{
    m_pFrameCache->addSpriteFramesWithFile("shoot_bg.plist");
    m_pFrameCache->addSpriteFramesWithFile("shoot.plist");
}

bool GameMain::init()
{
    bool bRet = true;
    if(!BaseScene::init())
    {
        bRet = false;
    }
    enemies = CCArray::create();
    bullets = CCArray::create();
    enemies->retain();
    bullets->retain();

    srand((unsigned)time(NULL));
    m_pBgNode = CCSpriteBatchNode::createWithTexture(m_pFrameCache->spriteFrameByName("background.png")->getTexture());
    addChild(m_pBgNode);
    m_pBattleBatchNode = CCSpriteBatchNode::createWithTexture(m_pFrameCache->spriteFrameByName("hero1.png")->getTexture());
    addChild(m_pBattleBatchNode);

    __initAnimation();
    __initBackground();
    __initCopyRight();
    return bRet;
}

inline void GameMain::__initBackground()
{
    CCSprite *bg1 = CCSprite::createWithSpriteFrameName("background.png");
    CCSprite *bg2 = CCSprite::createWithSpriteFrameName("background.png");
    m_pBgNode->getTexture()->setAliasTexParameters();
    bg1->setAnchorPoint(ccp(0,0));
    bg2->setAnchorPoint(ccp(0,0));
    bg1->setPosition(ccp(0,0));
    bg2->setPosition(ccp(0,m_nBgHeight-3));
    m_pBgNode->addChild(bg1);
    m_pBgNode->addChild(bg2);
}

void GameMain::__scrollBackground()
{
    m_pBgNode->setPositionY(0);
    CCActionInterval *moveDown = CCMoveTo::create(5, ccp(0, -m_nBgHeight));
    CCCallFunc *resetHandler = CCCallFunc::create(this, callfunc_selector(GameMain::__scrollBackground));
    CCSequence *moveSeq = CCSequence::create(moveDown,resetHandler,NULL);
    m_pBgNode->runAction(moveSeq);
}

inline void GameMain::__initAnimation()
{
    __addAnimation("game_loading%d.png",1,4,2,"loading");
    __addAnimation("hero%d.png",1,2,8,"hero");
    __addAnimation("enemy1_down%d.png",1,4,12,"enemy1_down");
    __addAnimation("enemy2_down%d.png",1,4,8,"enemy2_down");
    __addAnimation("enemy3_down%d.png",1,6,8,"enemy3_down");
    __addAnimation("hero_blowup_n%d.png",1,4,8,"hero_down");
    __addAnimation("enemy3_n%d.png",1,2,8,"enemy3");
}

inline void GameMain::__initCopyRight()
{
    m_pCopyRight = CCSprite::createWithSpriteFrameName("shoot_copyright.png");
    m_pCopyRight->setPosition(ccp(VisibleRect::center().x,VisibleRect::top().y-200));
    m_pBgNode->addChild(m_pCopyRight);
    m_pLoading = CCSprite::createWithSpriteFrameName("game_loading1.png");
    m_pLoading->setPosition(VisibleRect::center());
    CCAnimate *loadingAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("loading"));
    CCCallFunc *loadingCallback = CCCallFunc::create(this,callfunc_selector(GameMain::__gameStart));
    CCRepeat *repeate = CCRepeat::create(loadingAnimate,1);
    CCSequence *loadingSeq = CCSequence::create(repeate,loadingCallback,NULL);
    m_pLoading->runAction(loadingSeq);
    m_pBgNode->addChild(m_pLoading);
}

void GameMain::__gameStart()
{
    scheduleUpdate();
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
    __scrollBackground();
    m_pBgNode->removeChild(m_pLoading,true);
    m_pBgNode->removeChild(m_pCopyRight,true);
    __createHero();
    __createEnemy1();
    __createEnemy2();
    __createEnemy3();
}

void GameMain::__restart()
{
    __initCopyRight();
}

void GameMain::__createHero()
{
    m_pHero = Hero::createHero();
    m_pHero->setPosition(ccp(m_iWinSize.width/2,(m_pHero->getContentSize()).height/2));
    m_pBattleBatchNode->addChild(m_pHero);
}

void GameMain::__gameOver()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
}

void GameMain::__addAnimation( const char *prefix,int start,int end,int fps,const char *animationName )
{
    CCArray *spriteFrames = CCArray::createWithCapacity(end);
    for(int i=start; i<=end; i++)
    {
        const char *pszName = CCString::createWithFormat(prefix,i)->getCString();
        CCSpriteFrame *spriteFrame = m_pFrameCache->spriteFrameByName(pszName);
        spriteFrames->addObject(spriteFrame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(spriteFrames,1.0/fps);
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation,animationName);
}

void GameMain::__createEnemy1()
{
    float time = (rand()%10)/30.0f+0.3f;
    __createEnemy(1,time,callfunc_selector(GameMain::__createEnemy1));
}
void GameMain::__createEnemy2()
{
    float time = rand()%3+2;
    __createEnemy(2,time,callfunc_selector(GameMain::__createEnemy2));
}
void GameMain::__createEnemy3()
{
    float time = rand()%8+8;
    __createEnemy(3,time,callfunc_selector(GameMain::__createEnemy3));
}

void GameMain::__createEnemy(int type, float time,SEL_CallFunc selector )
{
    BaseEnemy *enemy = BaseEnemy::createEnemy(type);
    m_pBattleBatchNode->addChild(enemy);
    CCDelayTime *delay = CCDelayTime::create(time);
    CCCallFunc *delayCall = CCCallFunc::create(this,selector);
    CCSequence *seq = CCSequence::create(delay,delayCall,NULL);
    runAction(seq);
}

void GameMain::update(float del)
{
    CCArray *waitRemoveBullet = CCArray::create();
    CCArray *waitRemoveEnemy = CCArray::create();
    CCObject *enemyObj = NULL;
    CCObject *bulletObj = NULL;
    CCARRAY_FOREACH(enemies, enemyObj)
    {
        BaseEnemy *enemy = (BaseEnemy*)enemyObj;
        CCARRAY_FOREACH(bullets, bulletObj)
        {
            Bullet *bullet = (Bullet*)bulletObj;
            if(bullet->getLock())
            {
                continue;
            }
            CCPoint bulletPos = bullet->getPosition();
            int enemyLeft = enemy->getPositionX()-enemy->getContentSize().width/2;
            int enemyRight = enemy->getPositionX()+enemy->getContentSize().width/2;
			 int type = enemy->getType();
            if(bulletPos.y >= enemy->getPositionY()+type*5&&bulletPos.x>enemyLeft&&bulletPos.x<enemyRight)
            {
                bullet->setLock(true);
                waitRemoveBullet->addObject(bullet);
                enemy->m_nHP -= 1;
				enemy->state = 1;
				enemy->stopBaseAction();
                if(enemy->getType()!=1)
                {
                    const char *hitTName = CCString::createWithFormat("enemy%d_hit.png",enemy->getType())->getCString();
                    enemy->setDisplayFrame(m_pFrameCache->spriteFrameByName(hitTName));
                }
                if(enemy->m_nHP<=0)
                {
                    waitRemoveEnemy->addObject(enemy);
					
                }
            }
            else if(enemy->state==1)
            {
				enemy->state = 0;
                const char *hitTName = CCString::createWithFormat("enemy%d.png",type)->getCString();
				if(type==3){
					hitTName="enemy3_n1.png";
				}
                enemy->setDisplayFrame(m_pFrameCache->spriteFrameByName(hitTName));
				enemy->runBaseAction();
            }
        }
    }
    CCARRAY_FOREACH(waitRemoveEnemy, enemyObj)
    {
        BaseEnemy *enemy = (BaseEnemy*)enemyObj;
        enemies->removeObject(enemy,false);
		enemy->state = 2;
		const char *downName = CCString::createWithFormat("enemy%d_down",enemy->getType())->getCString();
		CCAnimate *downAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(downName));
		CCCallFunc *downCall = CCCallFunc::create(enemy,callfunc_selector(BaseEnemy::removeFromParent));
		enemy->runAction(CCSequence::create(downAnimate,downCall,NULL));
    }
    CCARRAY_FOREACH(waitRemoveBullet, bulletObj)
    {
        Bullet *bullet = (Bullet*)bulletObj;
        bullets->removeObject(bullet,false);
        bullet->removeFromParent();
    }
}

void GameMain::__addAnimationFromArray( std::string *names,int length,int fps,const char *animateName )
{

}
