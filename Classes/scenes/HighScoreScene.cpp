#include "HighScoreScene.h"
#include "SimpleAudioEngine.h"

#define TRANSITION_TIME 0.5

USING_NS_CC;

Scene* HighScoreScene::createScene() {
    auto scene = Scene::create();
    auto layer = HighScoreScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool HighScoreScene::init() {

    if ( !Layer::init() ) {
        return false;
    }

    _model = new Highscore();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto backgroundSprite = Sprite::create("res/space.png");
    backgroundSprite->setScale(0.35);
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    auto start_btn = MenuItemImage::create("res/button.png", "res/button_clicked.png", CC_CALLBACK_1(HighScoreScene::goToMainScene, this) );
    start_btn->setPosition(Vec2(visibleSize.width/1.5, visibleSize.height/1.1 + origin.y  - start_btn->getContentSize().height));
    
    auto menu = Menu::create(start_btn, NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);

//    displayScores();

    return true;

}

void displayScores() {
    // TODO display score table using
//    _model.getList();
}


void HighScoreScene::goToMainScene(Ref *sender) {
    this->cleanup();
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene) );
}
