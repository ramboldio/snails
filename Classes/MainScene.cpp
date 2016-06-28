#include "MainScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <cstring>
#define COCOS2D_DEBUG 1
using namespace std;

USING_NS_CC;

/*
 * TODOs
 * Physics Body -> Polygon
 * no click when flying 
 * Track Landing 
 * Goal
 * Game End Screen
 * Score Counter (Distance + Tries)
 * Move Perspective / Background
 */


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
    //auto space = Sprite::create("res/bg_2.png");
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
    ground->setScale(1.0f, 3.0f);
    
    this->addChild(ground, 1);
    
    
    auto tree = Sprite::create("res/spaceTree.png");
    auto treeBody = PhysicsBody::createBox(Size(100.0f, 500.0f), PhysicsMaterial(0.1f, 1.0f, 0.5f));
    treeBody->setDynamic(false);
    tree->setPosition(Vec2(800.0f, 250.0f));
    //tree->setPosition(Vec2(200.0f, 250.0f));
    tree->setPhysicsBody(treeBody);
    tree->setScale(0.4);
    
    this->addChild(tree, 1);
    
    
    // test-snail :)
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/spritesheet.plist");
    //_snail = Sprite::createWithSpriteFrameName("snail_base.png");
    
    //_snail = Sprite::create("res/norm/snail_base.png");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/norm/spritesheettest.plist");
    
    _snail = Sprite::createWithSpriteFrameName("snail_base.png");
    
    auto snailBody = PhysicsBody::createBox(Size(1200.0f, 600.0f), PhysicsMaterial(0.5f, 0.2f, 5.0f));
    snailBody->setMass(10.0f);
    _snail->setPosition(Vec2(400.0f, 500.0f));
    _snail->setPosition(Vec2(200.0f, 200.0f));
    _snail->setScale(scaleFactorSnail);
    _snail->setPhysicsBody(snailBody);
    
    this->addChild(_snail, 2);
    
    
    auto button = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png", "disabled_reButton.png");
    button->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2, origin.y + visibleSize.height-closeItem->getContentSize().height/2));
    
    //button->setTitleText("Button Text");
    
    button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                _snail->setPosition(Vec2(200.0f, 200.0f));
                CCLOG("Button 1 clicked");
                break;
            default:
                break;
        }
    });
    
    this->addChild(button);


    
    
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
    //Rect rect = Rect(0, 0, s.width, s.height);
    Rect rect = Rect(_snail->getPositionX()-_snail->getContentSize().width*scaleFactorSnail/2, _snail->getPositionY()- _snail->getContentSize().height*scaleFactorSnail/2, _snail->getContentSize().width*scaleFactorSnail, _snail->getContentSize().height*scaleFactorSnail);
    
    //Check the click area
    if (rect.containsPoint(locationInNode)) {

        log("toch began... x = %f, y = %f", locationInNode.x, locationInNode.y);
        _delta = touch->getLocation();
        _tap = touch->getLocation();
        
        return true;
    }
    return false;
}

void MainScene::onTouchMoved(Touch* touch, Event* event) {
    if (touch != nullptr) {
        _tap = touch->getLocation();
        _snail->setTexture("res/norm/snail_touch.png");
        log("tap... x = %f, y = %f", _tap.x, _tap.y);
    }
}

void MainScene::onTouchEnded(Touch* touch, Event* event) {
    if (touch != nullptr && _tap.y - _delta.y!=0 && _tap.x - _delta.x != 0) {
        Vec2 force = Vec2( -(_tap.x - _delta.x)*20.0f, 350 + (abs(_tap.y - _delta.y))*20.0f);
        CCLOG("Force: %f %f", force.x, force.y);
        _snail->getPhysicsBody()->applyImpulse(force);
        _snail->setTexture("res/norm/snail_air_lines.png");
    }
}

void MainScene::menuCloseCallback(Ref* pSender){
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
