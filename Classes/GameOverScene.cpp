#include "GameOverScene.h"
#include "MainScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameOverScene::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto backgroundSprite = Sprite::create("res/gameover.png");
    backgroundSprite->setScale(0.32);
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    
    
    auto start_btn = MenuItemImage::create("res/tryagain.png", "res/tryagain.png", CC_CALLBACK_1(GameOverScene::goToMainScene, this) );
    start_btn->setScale(0.3);
    start_btn->setPosition(Vec2(visibleSize.width/2.7, visibleSize.height/1.2 + origin.y  - start_btn->getContentSize().height));
    
    auto menu = Menu::create(start_btn, NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);

    
    
    
    return true;
}

void GameOverScene::goToMainScene(Ref *sender) {
    auto scene = MainScene::createScene();
    
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene) );
}
