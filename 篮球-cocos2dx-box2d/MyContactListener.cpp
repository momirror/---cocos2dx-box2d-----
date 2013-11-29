//
//  MyContactListener.cpp
//  篮球-cocos2dx-box2d
//
//  Created by msp on 13-11-8.
//
//

#include "MyContactListener.h"



/**
	碰撞开始
	@param contact 碰撞   
 */
void MyContactListener:: BeginContact(b2Contact* contact)

{
    CCLOG("BeginContact");
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    CCSprite* spriteA = (CCSprite*)bodyA->GetUserData();
    CCSprite* spriteB = (CCSprite*)bodyB->GetUserData();
    
}

/**
	碰撞结束
	@param contact 碰撞
 */
void MyContactListener::EndContact(b2Contact* contact)

{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    CCSprite* spriteA = (CCSprite*)bodyA->GetUserData();
    CCSprite* spriteB = (CCSprite*)bodyB->GetUserData();
    CCLOG("EndContact");
    
}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    CCLOG("PreSolve");
    // handle pre-solve event 
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    CCLOG("PostSolve");
    // handle post-solve event
}