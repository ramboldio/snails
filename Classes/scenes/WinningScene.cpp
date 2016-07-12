#include "WinningScene.h"
#include "MainScene.h"
#include "ui/CocosGUI.h"

#define TRANSITION_TIME 0.5
USING_NS_CC;

Scene* WinningScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WinningScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool WinningScene::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto backgroundSprite = Sprite::create("res/gewinner.png");
    backgroundSprite->setScale(0.32);
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    Vector<MenuItem*> items;
    
    auto start_btn = MenuItemImage::create("res/button.png", "res/button_clicked.png", CC_CALLBACK_1(WinningScene::goToMainScene, this) );
    start_btn->setScale(0.8);
    start_btn->setPosition(Vec2(visibleSize.width/1.5, visibleSize.height/1.2 + origin.y  - start_btn->getContentSize().height));
    
    items.pushBack(start_btn);

    /*auto menu = Menu::create(start_btn, NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);*/
    
    auto score_btn = MenuItemImage::create("res/highscore_button.png", "res/highscore_button.png", CC_CALLBACK_1(WinningScene::openHighscorePopup, this) );
    score_btn->setPosition(Vec2(visibleSize.width - 130, 100));
    score_btn->setScale(0.4);
    score_btn->setRotation(-30);
    items.pushBack(score_btn);

    auto menu = Menu::createWithArray(items);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);

    
    return true;
}

void WinningScene::openHighscorePopup (Ref *sender) {
    auto _popup = HighscorePopup::createPopup();
    this->addChild(_popup, 4);
}

void WinningScene::goToMainScene(Ref *sender) {
    auto scene = MainScene::createScene();
    this->getScene()->cleanup();
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene) );
}
