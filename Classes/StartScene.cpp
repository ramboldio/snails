#include "StartScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

#define TRANSITION_TIME 0.5

USING_NS_CC;

Scene* StartScene::createScene() {
    auto scene = Scene::create();
    auto layer = StartScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool StartScene::init() {

    if ( !Layer::init() ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto backgroundSprite = Sprite::create("res/space.png");
    backgroundSprite->setScale(0.35);
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    
    
    auto start_btn = MenuItemImage::create("res/button.png", "res/button_clicked.png", CC_CALLBACK_1(StartScene::goToMainScene, this) );
    start_btn->setPosition(Vec2(visibleSize.width/1.5, visibleSize.height/1.1 + origin.y  - start_btn->getContentSize().height));
    
    auto menu = Menu::create(start_btn, NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    return true;

}

void StartScene::goToMainScene(Ref *sender) {
    this->cleanup();
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene) );
}
