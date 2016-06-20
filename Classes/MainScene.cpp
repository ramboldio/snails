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
    
    // background
    auto space = Sprite::create("res/space.png");
    space->setPosition(Vec2(visibleSize.width/2  + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(space);

    // exit-button
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2, origin.y + closeItem->getContentSize().height/2));
    //this->addChild(closeItem, 2);
    
    
    // ground
    auto ground = Sprite::create("res/ground.png");
    auto groundBody = PhysicsBody::createBox(Size(1024.0f, 50.0f), PhysicsMaterial(0.1f, 1.0f, 0.5f));
    groundBody->setDynamic(false);
    ground->setPosition(Vec2(_center.x, 16.0f));
    ground->setPhysicsBody(groundBody);
    
    this->addChild(ground, 1);
    
    
    // test-snail :)
    _snail = Sprite::create("res/snail.png");
    auto snailBody = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0.5f, 0.4f, 1.0f));
    snailBody->setMass(10.0f);
    _snail->setPosition(Vec2(400.0f, 500.0f));
    _snail->setPhysicsBody(snailBody);
    
    this->addChild(_snail, 2);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
   
    return true;
}

bool MainScene::onTouchBegan(Touch* touch, Event* event) {
    auto target = static_cast<Sprite*>(event->getCurrentTarget());

    //Get the position of the current point relative to the button
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    //Check the click area
    if (rect.containsPoint(locationInNode)) {

        log("toch began... x = %f, y = %f", locationInNode.x, locationInNode.y);
        _snail->setTexture("res/snail_red.png");
        _delta = touch->getLocation();
        
        return true;
    }
    return false;
}

void MainScene::onTouchMoved(Touch* touch, Event* event) {
    if (touch != nullptr) {
        _tap = touch->getLocation();
        log("tap... x = %f, y = %f", _tap.x, _tap.y);
    }
}

void MainScene::onTouchEnded(Touch* touch, Event* event) {
    if (touch != nullptr) {
        Vec2 force = Vec2( (_tap.x - _delta.x)*10.0f, 350 *10.0f + (_tap.y - _delta.y));
        CCLOG("Force: %f %f", force.x, force.y);
        _snail->getPhysicsBody()->applyImpulse(force);
        _snail->setTexture("res/snail.png");
    }
}



void MainScene::menuCloseCallback(Ref* pSender){
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}