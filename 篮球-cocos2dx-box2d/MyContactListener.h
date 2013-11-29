//
//  MyContactListener.h
//  篮球-cocos2dx-box2d
//
//  Created by msp on 13-11-8.
//
//

#ifndef _____cocos2dx_box2d__MyContactListener__
#define _____cocos2dx_box2d__MyContactListener__

#include <iostream>
#include "Box2D.h"
#include "cocos2d.h"
using namespace cocos2d;

class MyContactListener:public b2ContactListener
{
    
    
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
};


#endif /* defined(_____cocos2dx_box2d__MyContactListener__) */
