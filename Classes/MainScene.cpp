#include "MainScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include <cstring>
#define COCOS2D_DEBUG 1
using namespace std;

USING_NS_CC;

MainScene::MainScene(){}

MainScene::~MainScene(){}

Scene* MainScene::createScene() {
    
    auto scene = Scene::createWithPhysics();
    auto layer = MainScene::create();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -350.0f));
    scene->addChild(layer);
    
    return scene;
}

bool MainScene::init() {
    
    if ( !Layer::init() ) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _screenSize = visibleSize;
    _delta = Vec2(0,0);
    _center = Vec2(_screenSize.width * 0.5, _screenSize.height * 0.5);
    
    // exit-button
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2, origin.y + closeItem->getContentSize().height/2));
    //this->addChild(closeItem, 2);
    
    
    // walls
    auto wallBody1 = PhysicsBody::createBox(
                                            Size(32.0f, origin.y + visibleSize.height),
                                            PhysicsMaterial(0.1f, 1.0f, 0.5f)
                                            );
    auto wallBody2 = PhysicsBody::createBox(
                                            Size(32.0f,  origin.y + visibleSize.height*3),
                                            PhysicsMaterial(0.1f, 1.0f, 0.5f)
                                            );
    
    
    wallBody1->setDynamic(false);
    wallBody1->setPositionOffset(Vec2(visibleSize.width, visibleSize.height-visibleSize.height/2));
    wallBody1->setName("wall1");
    wallBody1->setTag(1);
    
    wallBody2->setDynamic(false);
    wallBody2->setPositionOffset(Vec2(-visibleSize.width, 0));
    wallBody2->setName("wall2");
    wallBody2->setTag(2);
    
    
    this->addComponent(wallBody1);
    this->addComponent(wallBody2);
    
    
    // background
    auto space = Sprite::create("res/space.png");
    space->setPosition(Vec2(visibleSize.width/2  + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(space);
    
    
    // ground
    auto ground = Sprite::create("res/ground.png");
    auto groundBody = PhysicsBody::createBox(Size(2048.0f, 50.0f), PhysicsMaterial(1.0f, 0.0f, 1.0f));
    groundBody->setDynamic(false);
    ground->setPosition(Vec2(_center.x, 16.0f));
    ground->setPhysicsBody(groundBody);
    this->addChild(ground, 1);
    
    
<<<<<<< HEAD
    // test-snail :)
    _snail = Sprite::create("res/snail.png");
    auto snailBody = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.5f, 0.4f, 1.0f));
    snailBody->setMass(10.0f);
    
    _snail->setPosition(Vec2(400.0f, 500.0f));
    _snail->setPhysicsBody(snailBody);
    
    this->addChild(_snail, 2);
=======
    createSnail();
>>>>>>> origin/development
    
    // Camera
    float playfield_width = _screenSize.width * 2.0; // make the x-boundry 2 times the screen width
    float playfield_height = _screenSize.height * 2.0; // make the y-boundry 2 times the screen height
    this->runAction(Follow::create(_snail, Rect( _center.x - playfield_width/2, _center.y - playfield_height/4 , playfield_width, playfield_height)));
    
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

   
    return true;
}

void MainScene::createSnail() {

    // test-snail :)
    _snail = Sprite::create("res/snail.png");
    auto snailBody = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(1.0f, 0.1f, 1.0f));
    snailBody->setMass(10.0f);
    
    snailBody->setContactTestBitmask(0xFFFFFFFF);
    snailBody->setCategoryBitmask(0x02);    // 0011
    snailBody->setCollisionBitmask(0x01);   // 0001
    snailBody->setRotationEnable(false);
    
    _snail->setPosition(Vec2(400.0f, 500.0f));
    _snail->setPhysicsBody(snailBody);
    this->addChild(_snail, 2);
}


void MainScene::update(float dt) { }

bool MainScene::onContactBegin(PhysicsContact& contact) { }

void MainScene::onTouchesBegan(const std::vector<Touch*> &touches, Event* event) {
    for (auto touch : touches) {
        if (touch != nullptr) {
            _delta = touch->getLocation();
        }
    }
}

void MainScene::onTouchesMoved(const std::vector<Touch*> &touches, Event* event){
    for (auto touch : touches) {
        if (touch != nullptr) {
            _tap = touch->getLocation();
        }
    }
}

void MainScene::onTouchesEnded(const std::vector<Touch*> &touches, Event* event) {
    for (auto touch : touches) {
        if (touch != nullptr) {
            Vec2 tap = touch->getLocation();
            _force = Vec2( (tap.x - _delta.x)*10.0f, 350 *10.0f + (tap.y - _delta.y));
            CCLOG("Force: %f %f", _force.x, _force.y);
            _snail->getPhysicsBody()->applyImpulse(_force);
        }
    }
}


void MainScene::menuCloseCallback(Ref* pSender){
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}