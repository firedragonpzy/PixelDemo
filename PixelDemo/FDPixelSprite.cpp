//
//  FDPixelSprite.cpp
//  PixelDemo
//
//  Created by firedragonpzy on 13-2-19.
//
//

#include "FDPixelSprite.h"


FDPixelSprite::FDPixelSprite()
{}
FDPixelSprite::~FDPixelSprite()
{}

FDPixelSprite* FDPixelSprite::create(const char *pszFileName)
{
    FDPixelSprite *sprite = new FDPixelSprite();
    if (sprite && sprite->initWithFile(pszFileName)) {
        sprite->setName(pszFileName);
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    sprite = NULL;
    return NULL;
}


void FDPixelSprite::onEnter()
{
    CCSprite::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}


void FDPixelSprite::onExit()
{
    CCSprite::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


bool FDPixelSprite::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (this->isContainTouchLocation(pTouch) ) {
        ccColor4B c = {0, 0, 0, 0};
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCPoint touchPoint = pTouch->getLocationInView();
        
        CCSize cSize = this->getContentSize();
        CCPoint point =this->getAnchorPointInPoints();
        point = ccp(cSize.width - point.x,cSize.height- point.y);
        CCPoint pos(this->getPositionX() - point.x,winSize.height-this->getPositionY()- point.y);
        
        CCPoint localPoint = ccp(touchPoint.x - pos.x,
                                 touchPoint.y -pos.y);
        
        unsigned int x = localPoint.x, y = localPoint.y;
        
        //This method is currently only supports symmetric image
        //unsigned char *data_ = this->getTexture()->getFDImageData();
        
        //Efficiency of this method is relatively low
        CCImage * img = new CCImage();
        img->initWithImageFileThreadSafe(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(TESTPNG) );
        unsigned char *data_ = img->getData();
        
        
        unsigned int *pixel = (unsigned int *)data_;
        pixel = pixel + (y * (int)this->getContentSize().width)* 1 + x * 1;
        c.r = *pixel & 0xff;
        c.g = (*pixel >> 8) & 0xff;
        c.b = (*pixel >> 16) & 0xff;
        c.a = (*pixel >> 24) & 0xff;
        if (c.a == 0) {
            CCLog("firedragonpzy:ccTouchBegan----------");
            return false;
        }else
        {
            return true;
        }
    }
    return false;
}


void FDPixelSprite::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint pos = this->getPosition();
    CCPoint sub = pTouch->getDelta();
    this->setPosition(ccpAdd(pos, sub));
}


void FDPixelSprite::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLog("firedragonpzy:ccTouchEnded");
}


CCRect FDPixelSprite::atlasRect()
{
    CCSize cSize = this->getContentSize();
    CCPoint point = this->getAnchorPointInPoints();
    return CCRectMake( -point.x, -point.y, cSize.width,cSize.height);
}


bool FDPixelSprite::isContainTouchLocation(cocos2d::CCTouch *pTouch)
{
   return this->atlasRect().containsPoint(convertTouchToNodeSpaceAR(pTouch));
}








