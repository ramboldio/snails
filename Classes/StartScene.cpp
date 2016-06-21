#include "StartScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

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
    
    auto backgroundSprite = Sprite::create("res/background_start.png");
    backgroundSprite->setScale(1.5);
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    auto gameover_label = Label::createWithTTF("Snails Game!", "fonts/Marker Felt.ttf", 32);
    gameover_label->setColor(Color3B(0, 0, 0));
    gameover_label->setPosition(Vec2(visibleSize.width/2  + origin.x, visibleSize.height/2 + origin.y));
    
    this->addChild(gameover_label, 1);
    
    auto retryItem = MenuItemImage::create("res/btn_normal.png", "res/btn_clicked.png", CC_CALLBACK_1(StartScene::GoToMainScene, this) );
    retryItem->setPosition(Vec2(visibleSize.width/2  + origin.x, visibleSize.height/2 + origin.y - gameover_label->getContentSize().height - retryItem->getContentSize().height));
    
    auto menu = Menu::create(retryItem, NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    return true;

}

void StartScene::GoToMainScene(Ref *sender) {
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene) );
}
