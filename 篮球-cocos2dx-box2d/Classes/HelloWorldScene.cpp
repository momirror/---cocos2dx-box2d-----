//
//  HelloWorldScene.cpp
//  篮球-cocos2dx-box2d
//
//  Created by msp on 13-11-6.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <CoreGraphics/CoreGraphics.h>

using namespace CocosDenshion;

#define PTM_RATIO 32
enum 
{
	kTagTileMap = 1,
	kTagSpriteManager = 1,
	kTagAnimation1 = 1,
}; 

HelloWorld::HelloWorld()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    //篮球
    m_pBall = CCSprite::spriteWithFile("Ball.jpg",CCRect(0,0,52,52));
    m_pBall->setPosition(ccp(100,200));
    this->addChild(m_pBall);
    
    m_pBall2 = CCSprite::spriteWithFile("Ball.jpg",CCRect(0,0,52,52));
    m_pBall2->setPosition(ccp(50,200));
    this->addChild(m_pBall2);
    
    //世界
    b2Vec2 gravity = b2Vec2(0.0f,-10.0f);//表示x、y方向的作用力
    bool bSleep = true;
    m_pWorld = new b2World(gravity,bSleep);//用(0,0f,-30.0f)作为这个世界的重力系统。允许物体在不发生碰撞时进入sleep状态，节约系统资源
    
    /**********给这个世界制订四个看不见，碰得着的边界*********/
    b2BodyDef groundBodyDef;//定义
    groundBodyDef.position.Set(0, 0);
    
    b2Body * groundBody = m_pWorld->CreateBody(&groundBodyDef);//用world创建body,会自动进行相关的内存管理
    
    b2PolygonShape groundBox;//多边形形状
    b2FixtureDef     boxShapeDef;//边框形状定义
    
    boxShapeDef.shape = &groundBox;

    /***box2d的坐标系与cocos2d一样，都是以左下角为原点。***/
    groundBox.SetAsEdge(b2Vec2(0,0), b2Vec2(screenSize.width/PTM_RATIO,0));//下边界
    groundBody->CreateFixture(&boxShapeDef);

    groundBox.SetAsEdge(b2Vec2(0,0), b2Vec2(0,screenSize.height/PTM_RATIO));//左边界
    groundBody->CreateFixture(&boxShapeDef);

    groundBox.SetAsEdge(b2Vec2(0,screenSize.height/PTM_RATIO), b2Vec2(screenSize.width/PTM_RATIO,screenSize.height/PTM_RATIO));//上边界
    groundBody->CreateFixture(&boxShapeDef);

    groundBox.SetAsEdge(b2Vec2(screenSize.width/PTM_RATIO,screenSize.height/PTM_RATIO), b2Vec2(screenSize.width/PTM_RATIO,0));//右边界
    groundBody->CreateFixture(&boxShapeDef);
    
    
    //SetAsEdge的两个参数表示一个矩形的两个对角点
    
    
    
    
    /********篮球的body和形状***********/
    //body
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;//设置为动态刚体
    ballBodyDef.position.Set(100/PTM_RATIO, 200/PTM_RATIO);
    ballBodyDef.userData = m_pBall;//把篮球精灵赋给userData;
    m_pBody = m_pWorld->CreateBody(&ballBodyDef);
    
    ballBodyDef.position.Set(50/PTM_RATIO, 200/PTM_RATIO);
    ballBodyDef.userData = m_pBall2;//把篮球精灵赋给userData;
    m_pBody2 = m_pWorld->CreateBody(&ballBodyDef);
    

    //形状
    b2CircleShape circle;
    circle.m_radius = 26.0/PTM_RATIO;
    
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;//密度
    ballShapeDef.friction = 0.2f;//摩擦力
    ballShapeDef.restitution = 1.0f;//恢复力
    m_pBody->CreateFixture(&ballShapeDef);
    
    ballShapeDef.density = 0.5f;//密度
    m_pBody2->CreateFixture(&ballShapeDef);
    
//    //距离关节
//    b2Vec2 anchor1 = m_pBody->GetWorldCenter();//锚点
//    b2Vec2 anchor2 = m_pBody2->GetWorldCenter();//锚点
//    b2DistanceJointDef joinDef;
//    joinDef.Initialize(m_pBody, m_pBody2, anchor1, anchor2);
//    joinDef.collideConnected = true;//允许碰撞
//    m_pWorld->CreateJoint(&joinDef);//通过世界来创建关节
//    
    //旋转关节
    b2RevoluteJointDef revolutejoinDef;
    revolutejoinDef.Initialize(m_pBody, m_pBody2, m_pBody->GetWorldCenter());//围绕m_pBody的中心点来旋转
    b2Joint * revoluteJoin =  m_pWorld->CreateJoint(&revolutejoinDef);
    
    //带有限制和马达的关节
//    b2RevoluteJointDef limitMotorJoinDef;
//    limitMotorJoinDef.Initialize(m_pBody, m_pBody2, m_pBody->GetWorldCenter());//围绕m_pBody的中心点来旋转
//    limitMotorJoinDef.lowerAngle = -0.5f*b2_pi;//-90度
//    limitMotorJoinDef.upperAngle = 0.25f*b2_pi;//45度
//    limitMotorJoinDef.maxMotorTorque = 10.0f;//马达扭矩，会产生关节转动起来的力，扭矩与速度成反比
//    limitMotorJoinDef.enableLimit = true;//限制
//    limitMotorJoinDef.motorSpeed = 10.0f;
//    limitMotorJoinDef.enableMotor = true;
//    m_pWorld->CreateJoint(&limitMotorJoinDef);
    
    //移动关节
    b2PrismaticJointDef prismaticJoinDef;
    b2Vec2 worldAxis(1.0f,0.0f);//指向屏幕外面的轴，物体将沿着这条轴移动
    prismaticJoinDef.Initialize(m_pBody, m_pBody2, m_pBody->GetWorldCenter(), worldAxis);
    prismaticJoinDef.lowerTranslation = -5.0f;
    prismaticJoinDef.upperTranslation = 2.5f;
    prismaticJoinDef.enableLimit = true;
    prismaticJoinDef.motorSpeed = 0.0f;
    prismaticJoinDef.enableMotor = true;
    b2Joint * prismaticJoin = m_pWorld->CreateJoint(&prismaticJoinDef);
    
//    //滑轮关节（滑轮组）
//    b2Vec2 anchor1 = m_pBody->GetWorldCenter();//物体1上的质点（锚点）
//    b2Vec2 anchor2 = m_pBody2->GetWorldCenter();//物体2上的质点（锚点）
//
//    b2Vec2 groundAnchor1(anchor1.x,anchor1.y+10.0f);//物体1上方的滑轮悬挂点
//    b2Vec2 groundAnchor2(anchor2.x,anchor2.y+10.0f);//物体2上方的滑轮悬挂点
//
//    float32 ratio = 1.0f;//滑动系数
//    b2PulleyJointDef pulleyJoinDef;
//    pulleyJoinDef.Initialize(m_pBody, m_pBody2, groundAnchor1, groundAnchor2, anchor1, anchor2, ratio);
//    pulleyJoinDef.maxLengthA = 18.0f;//??
//    pulleyJoinDef.maxLengthB = 20.0f;//??
//    m_pWorld->CreateJoint(&pulleyJoinDef);
//
    
//    //齿轮关节 ????
//    m_pBody->SetType(b2_staticBody);
//    b2GearJointDef gearJoinDef;
//    gearJoinDef.bodyA = m_pBody;//bodyA必须是静态的
//    gearJoinDef.bodyB = m_pBody2;
//    gearJoinDef.joint1 = revoluteJoin;
//    gearJoinDef.joint2 = prismaticJoin;
//    gearJoinDef.ratio = 2.0f*b2_pi/30.0f;
//    m_pWorld->CreateJoint(&gearJoinDef);

    
    MyContactListener * listener = new MyContactListener();
    m_pWorld->SetContactListener(listener);
    
    
    
    
    
    schedule(schedule_selector(HelloWorld::tick));

}

HelloWorld::~HelloWorld()
{
	delete m_pWorld;//会一并删除世界对象里面的物体
	m_pWorld = NULL;
    
    m_pBody = NULL;
	
	//delete m_debugDraw;
}


void HelloWorld::tick(ccTime dt)
{
//    CCLOG("%f",dt);
    m_pWorld->Step(dt, 10, 10);//dt为时间步，后面两个参数分别为速度迭代次数和位置迭代次数，一般为8～10。每次查询物体和关节的信息之前，都要先执行这个函数来获得最新信息。dt通常为1/60.
    for(b2Body * b = m_pWorld->GetBodyList();b;b = b->GetNext())
    {
        if(b->GetUserData() != NULL)
        {
            CCSprite * ball = (CCSprite*)b->GetUserData();
            
            //位置
            ball->setPosition(ccp(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO));
            
            //角度
            ball->setRotation(-1*CC_RADIANS_TO_DEGREES(b->GetAngle()));        }
    }
}



CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::node();
    CCLayer* layer = new HelloWorld();
    scene->addChild(layer);
    layer->release();

    return scene;
}
