//
//  HelloWorldScene.h
//  篮球-cocos2dx-box2d
//
//  Created by msp on 13-11-6.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "MyContactListener.h"


using namespace cocos2d;


//像素到米的转换
#define PTM_TATIO 32.0

class HelloWorld : public cocos2d::CCLayer {
    b2World     * m_pWorld;
    b2Body      * m_pBody;
    b2Body      * m_pBody2;
    CCSprite    * m_pBall;
    CCSprite    * m_pBall2;
public:
    ~HelloWorld();
    HelloWorld();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    void tick(cocos2d::ccTime dt);
    
};

#endif // __HELLO_WORLD_H__
