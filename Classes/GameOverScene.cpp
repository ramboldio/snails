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
    
    auto backgroundSprite = Sprite::create("res/background_start.png");
    backgroundSprite->setScale(1.5);
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    
    
    auto start_btn = MenuItemImage::create("res/button.png", "res/button_clicked.png", CC_CALLBACK_1(GameOverScene::goToMainScene, this) );
    start_btn->setPosition(Vec2(visibleSize.width/1.5, visibleSize.height + origin.y  - start_btn->getContentSize().height));
    
    auto menu = Menu::create(start_btn, NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);

    
    auto gameover_label = Label::createWithTTF("Game over!", "fonts/Marker Felt.ttf", 32);
    gameover_label->setColor(Color3B(0, 0, 0));
    gameover_label->setPosition(Vec2(visibleSize.width/2  + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(gameover_label, 1);
    
    
    return true;
}

void GameOverScene::goToMainScene(Ref *sender) {
    auto scene = MainScene::createScene();
    
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene) );
}
