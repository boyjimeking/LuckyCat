//
//  EquipInfoView.h
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-16.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __LuckyCat__EquipInfoView__
#define __LuckyCat__EquipInfoView__

#include <iostream>
#include "cocos2d.h"
#include "Basic.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum{
    kEquipHelmet      = 0,  //equip head;
    kEquipArms,             //equip arms;
    kEquipArmor,            //equip armor;
    kEquipShoes,            //equip shoes;
}EquipType;

typedef enum{
    kEquipTakeOff = 1,
    kEquipFontTakeOff = 13,
    kEquipPutOn = 11,
    kEquipFontPutOn = 12,
}EquipItemType;

class PlayerInfoDataManager;

class EquipInfoView
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCScrollViewDelegate
, public cocos2d::CCTextFieldDelegate
{
public:
    EquipInfoView();
    ~EquipInfoView();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EquipInfoView, create);
    
    //static EquipInfoView *create(cocos2d::CCObject * pOwner);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    
    virtual void scrollViewDidZoom(CCScrollView* view);
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    bool initEquipListView();
    
    void EquipViewBtnCallback(cocos2d::CCObject *pTarget);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void showEquipView();
    
    void hideEquipView();
    
    void setEquipInfoForType(EquipType type);
    
    void setPlayerEquipInfoForType(EquipType type);

    void sendPlayerEquipInfo();

    void responsePlayerEquipInfo(CCNode *pNode, void* data);
    
    void sendResetCurEquip();
    
    void responsePutOnCurEquip(CCNode *pNode, void* data);
    void responseTakeOffCurEquip(CCNode *pNode, void* data);
private:
    cocos2d::CCSprite   *m_sprEquipIcon;
    cocos2d::CCLabelTTF *m_labEquipName;
    cocos2d::CCLabelTTF *m_labEquipAttack;
    cocos2d::CCLabelTTF *m_labEquipDefence;
    cocos2d::CCLabelTTF *m_labEquipSpeed;
    cocos2d::CCLabelTTF *m_labEquipLife;
    
    CCScrollView* m_EquipListView;

    std::vector<cocos2d::CCLabelTTF> m_labsEquipProprety;
    std::vector<cocos2d::CCLabelTTF> m_labsPlayerEquipInfo;

    stActorUserEquipInfo *m_selectedEquipData;

    //void setEquipInfo(cocos2d::CCSprite *equipIcon, cocos2d::CCLabelTTF *equipName, std::vector<cocos2d::CCLabelTTF> &equipProprety);
    
    void setPlayerEquipInfo();
    
    void setEquipInfo(const stActorEquipInfo *info);
    
    void equipListMenuItemCallBack(CCNode *pSender);

};

class CCBReader;

class EquipInfoViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipInfoViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipInfoView);
};

#endif /* defined(__LuckyCat__EquipInfoView__) */