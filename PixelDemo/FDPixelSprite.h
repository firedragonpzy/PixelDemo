//
//  FDPixelSprite.h
//  PixelDemo
//
//  Created by firedragonpzy on 13-2-19.
//
//

#ifndef __PixelDemo__FDPixelSprite__
#define __PixelDemo__FDPixelSprite__
#define TESTPNG  "CloseSelected3.png"
#include "cocos2d.h"
USING_NS_CC;

class FDPixelSprite : public CCSprite, public CCTargetedTouchDelegate {
public:
    FDPixelSprite();
    virtual ~FDPixelSprite();
    
    void onEnter();
    void onExit();
    
    static FDPixelSprite* create( const char *pszFileName );

    
    CCRect atlasRect();
    bool isContainTouchLocation(CCTouch *pTouch);
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    CC_SYNTHESIZE(const char*, m_pName,Name);
};

#endif /* defined(__PixelDemo__FDPixelSprite__) */
