#include "MainScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include <cstring>
#define COCOS2D_DEBUG 1
using namespace std;

USING_NS_CC;
Label *label_score;
Scene *main_scene;
MainScene::MainScene(){}

MainScene::~MainScene(){}

Scene* MainScene::createScene() {
    
    main_scene = Scene::createWithPhysics();
    auto layer = MainScene::create();
    main_scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    main_scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -350.0f));
    main_scene->addChild(layer);
    
    return main_scene;
}

char* set_score_label(int _score){
    char text[256];
    sprintf(text,"Score: %d",_score);
    return text;
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
    
    label_score = Label::createWithTTF(set_score_label(score), "fonts/Marker Felt.ttf", 32);
    label_score->setPosition(Vec2(0, visibleSize.height + origin.y));
    this->addChild(label_score);

    
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
    auto ground = Sprite::create("res/ground_new.png");
    auto groundBody = PhysicsBody::createBox(Size(2048.0f, 200.0f), PhysicsMaterial(1.0f, 0.0f, 1.0f));
    groundBody->setDynamic(false);
    groundBody->setTag(0);
    groundBody->setContactTestBitmask(0xFFFFFFFFF);
    ground->setPosition(Vec2(_center.x, 16.0f));
    ground->setPhysicsBody(groundBody);
    this->addChild(ground, 1);
    
    createSnail();
    
    // Camera
    float playfield_width = _screenSize.width * 2.0; // make the x-boundry 2 times the screen width
    float playfield_height = _screenSize.height * 2.0; // make the y-boundry 2 times the screen height
    
    this->runAction(Follow::create(_snail->getSprite(), Rect( _center.x - playfield_width/2, _center.y - playfield_height/4 , playfield_width, playfield_height)));
    
    
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

PhysicsBody *createSnailBody(Sprite *snail_sprite){
    PhysicsBody *snail_body = PhysicsBody::createBox(Size(snail_sprite->getContentSize().width,
                                                       snail_sprite->getContentSize().height),
                                                  PhysicsMaterial(1.0f, 0.1f,1.0f));
    snail_body->setMass(10.0f);
    snail_body->setContactTestBitmask(0xFFFFFFFFF);
    snail_body->setCategoryBitmask(0x02);    // 0011
    snail_body->setCollisionBitmask(0x01);   // 0001
    snail_body->setRotationEnable(false);
    snail_body->setTag(1);
    
    return snail_body;
}

void MainScene::createSnail() {
    _snail = new Snail();
    _snail->getSprite()->setTexture("res/snail_base.png");
    _snail->getSprite()->setPosition(Vec2(_center.x, 156.6f)); // log("%f ", _snail->getSprite()->getPosition().y);
    _snail->getSprite()->setScale(0.1, 0.1);
    _snail->getSprite()->setPhysicsBody(createSnailBody(_snail->getSprite()));
    this->addChild(_snail->getSprite(), 2);
}


void MainScene::update(float dt) {
    
    if(_snail->ground_state and not _snail->base) {
        _snail->getSprite()->setTexture("res/snail_base.png");
        _snail->getSprite()->setPhysicsBody(createSnailBody(_snail->getSprite()));
        _snail->base = true;
    }
}

bool MainScene::onContactBegin(PhysicsContact& contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    if (nodeA && nodeB) { // ground and snail with ContactTestBitmask(0xFFFFFFFFF)
        _snail->ground_state = true;
    }

    return true;
}


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
            _snail->getSprite()->setTexture("res/snail_touch.png");
            _snail->base = false;
            _snail->getSprite()->setPhysicsBody(createSnailBody(_snail->getSprite()));
        }
    }
}

void MainScene::onTouchesEnded(const std::vector<Touch*> &touches, Event* event) {
    for (auto touch : touches) {
        if (touch != nullptr) {
            Vec2 tap = touch->getLocation();
            _force = Vec2( (tap.x - _delta.x)*10.0f, 350 *10.0f + (tap.y - _delta.y));
            CCLOG("Force: %f %f", _force.x, _force.y);
            if (_force.x < 0) {
                _snail->getSprite()->setScale(_snail->getSprite()->getScale() * -1, _snail->getSprite()->getScale());
            } else _snail->getSprite()->setScale(0.1, 0.1);

            _snail->getSprite()->setTexture("res/snail_air.png");
            _snail->base = false;
            
            _snail->getSprite()->setPhysicsBody(createSnailBody(_snail->getSprite()));
            _snail->getSprite()->getPhysicsBody()->applyImpulse(_force);
            _snail->ground_state = false;
        }
    }
}


void MainScene::menuCloseCallback(Ref* pSender){
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}