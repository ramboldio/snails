#include "MainScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include <cstring>
using namespace std;

USING_NS_CC;

MainScene::MainScene(){}

MainScene::~MainScene(){}

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    screenSize = visibleSize;
    
    auto space = Sprite::create("res/space.png");
    space->setPosition(Vec2(visibleSize.width/2  + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(space);

    
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2, origin.y + closeItem->getContentSize().height/2));
    this->addChild(closeItem, 1);
    
    return true;

    
}

void MainScene::menuCloseCallback(Ref* pSender){
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}