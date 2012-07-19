//
//  BossFightView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "BossFightView.h"

#define ACTION_INTERVAL_TIME    0.25f

#define TAG_MONSTER_SPRITE      9
#define TAG_LABEL_DES      10


void BossFightView::onEnter()
{
    CCLayerColor::onEnter();
    
    pMonsterSprite = NULL;
    
}

void BossFightView::initLayer()
{
    this->setColor(ccWHITE);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    //    cocos2d::CCLabelTTF *titleLabel = cocos2d::CCLabelTTF::create( "Monster Fight!", CCSizeMake(screanSize.width, 50),kCCVerticalTextAlignmentCenter,kCCVerticalTextAlignmentCenter,"Arial", 24); 
    //    titleLabel = CCLabelTTF::initWithString("Monster Fight!", "Arial", 50);
    
    CCLabelTTF *titleLabel = CCLabelTTF::create("Lord Voldemort", CCSizeMake(screanSize.width, 50), kCCTextAlignmentCenter,"Arial", 30);
    //cellLabel->setPosition(ccp(cellSize.width , cellSize.height )); 
    titleLabel->setAnchorPoint(ccp(0.5,0.5));
    titleLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height- 60));
    titleLabel->setColor(ccc3(255,55,0));
    this->addChild(titleLabel);
    
    CCSprite *_pMonsterSprite = CCSprite::create("bottom_1_7_1.png");
    _pMonsterSprite->setPosition(CCPointMake(screanSize.width*0.5f, 200));
    _pMonsterSprite->setScaleY(5);
    _pMonsterSprite->setScaleX(2.6);
    this->addChild(_pMonsterSprite);
    _pMonsterSprite->setTag(TAG_MONSTER_SPRITE);
    
    CCLabelTTF *dscLabel = CCLabelTTF::create("", CCSizeMake(screanSize.width, 50), kCCTextAlignmentCenter,"Arial", 30);
    //cellLabel->setPosition(ccp(cellSize.width , cellSize.height )); 
    dscLabel->setAnchorPoint(ccp(0.5,0.5));
    dscLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.75f));
    dscLabel->setColor(ccc3(255,55,0));
    this->addChild(dscLabel);
    dscLabel->setTag(TAG_LABEL_DES);
    
    dscLabel->setVisible(false);
    
    
    CCProgressTimer *middle = CCProgressTimer::create(CCSprite::create("extensions/sliderProgress.png"));
    middle->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle->setBarChangeRate(ccp(1, 1));
    addChild(middle);
    middle->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height- 80));
    
    
    fightAction();
}

void BossFightView::fightAction()
{
    mActionList.push_back(3);
    mActionList.push_back(1);
    mActionList.push_back(2);
    mActionList.push_back(1);
    
    
    this->playAction();
}

CCFiniteTimeAction * BossFightView::createSequece(unsigned int action_id)
{
    CCFiniteTimeAction *pAction = NULL;
    switch (action_id) {
        case 1:
        {
            CCSprite *pSprite = (CCSprite *)this->getChildByTag(TAG_MONSTER_SPRITE);
            CCPoint p_curPos = pSprite->getPosition();
            CCMoveTo *move1 = CCMoveTo::create(ACTION_INTERVAL_TIME, CCPointMake(p_curPos.x -30 , p_curPos.y -30));
            CCMoveTo *move2 = CCMoveTo::create(ACTION_INTERVAL_TIME, CCPointMake(p_curPos.x + 60, p_curPos.y +60));
            CCMoveTo *move3 = CCMoveTo::create(ACTION_INTERVAL_TIME, p_curPos);
            
            pAction = CCSequence::create(move1,move2,move3,CCCallFunc::create(this, callfunc_selector(BossFightView::playAction)),NULL);
            
            break;
        }
        case 2:
        {
            CCScaleBy *scale1 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1.2f);
            CCScaleBy *scale2 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1 / 1.2f);
            
            pAction = CCSequence::create(scale1,scale2,CCCallFunc::create(this, callfunc_selector(BossFightView::playAction)),NULL);
            
        }
        case 3:
        {
            CCFadeIn *fade1 = CCFadeIn::create(ACTION_INTERVAL_TIME);
            pAction = CCSequence::create(fade1,CCCallFunc::create(this, callfunc_selector(BossFightView::playAction)),NULL);
            
        }
        default:
            break;
    }
    
    return pAction;
}

void BossFightView::playAction()
{
    
    
    if ( mActionList.empty() == false )
    {
        unsigned int tAcitonID = mActionList[mActionList.size()-1];
        CCFiniteTimeAction *pAction = this->createSequece(tAcitonID);
        mActionList.pop_back();
        
        if(pAction)
        {
            if ( tAcitonID == 3 )
            {
                CCLabelTTF *pLabel = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_DES);
                pLabel->setColor(ccGREEN);
                pLabel->setString("你获得胜利!");
                pLabel->setVisible(true);
                pLabel->runAction(pAction);
            }
            else {
                CCSprite *pSprite = (CCSprite *)this->getChildByTag(TAG_MONSTER_SPRITE);
                pSprite->runAction(pAction);
            }
        }
    }
}