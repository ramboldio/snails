//
// Created by lukas on 08.07.16.
//

#include <ui/UIButton.h>
#include "HighscorePopup.h"


HighscorePopup::HighscorePopup() {
    _model = new Highscore();
}

HighscorePopup::~HighscorePopup() {}

HighscorePopup *HighscorePopup::createPopup() {

    HighscorePopup* a = new HighscorePopup();
    a->create();
    a->setColor(cocos2d::Color3B(0, 0, 0));

    a->setContentSize(Size(1, 1));
    a->setAnchorPoint(Vec2(0, 0));
    a->drawPopup();


    return a;
}

void HighscorePopup::drawPopup()
{
    _messageLabel = Label::createWithTTF("HIGHSCORES", "fonts/Pixel LCD-7.ttf", 32);
    _messageLabel->setColor(cocos2d::Color3B(255, 215, 0));
    _messageLabel->setPosition(Vec2(
            _popup_size.x / 2,
            _popup_size.y - _heading_margin_top
    ));
    
    Label* dateLabel = Label::createWithTTF("Date", "fonts/Pixel LCD-7.ttf", 25);
    dateLabel->setAnchorPoint(Vec2(0.0f,0.5f)); // left align
    dateLabel->setColor(cocos2d::Color3B(255, 115, 0));
    dateLabel->setPosition(Vec2(_table_margin_left, _popup_size.y - _heading_margin_top - _messageLabel->getContentSize().height));
    
    addChild(dateLabel, 1);
    
    Label* jumpsLabel = Label::createWithTTF("Jumps", "fonts/Pixel LCD-7.ttf", 25);
    jumpsLabel->setAnchorPoint(Vec2(0.0f,0.5f)); // left align
    jumpsLabel->setColor(cocos2d::Color3B(255, 115, 0));
    jumpsLabel->setPosition(Vec2(_table_margin_left + 450, _popup_size.y - _heading_margin_top - _messageLabel->getContentSize().height));
    
    addChild(jumpsLabel, 1);

    
    // addChild(_messageLabel, 1);

    Sprite* background = Sprite::create("res/highscore_background.png");
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    background->setPosition( Point( _popup_size.x / 2 + origin.x, _popup_size.y / 2 + origin.y) );
    background->setScale(0.4, 0.35);
    addChild(background, 0);

    drawEntries();

    initBackButton();
}


void HighscorePopup::draw(Renderer * renderer, const Mat4 & transform,
                      bool transformUpdated) {}

void HighscorePopup::drawEntries() {
    std::list<entry>* list = _model->getList();

    std::list<entry>::iterator iter = list->begin();

    int i = 0;
    while(iter != list->end())
    {
        entry& e = *iter;
        drawEntry(i, e.name, e.score);
        iter++; i++;
    }
}

void HighscorePopup::drawEntry(int pos, std::string &name, int &score) {
    
    Label* nameLabel = Label::createWithTTF(std::to_string(pos +1) + ". " + name, "fonts/Pixel LCD-7.ttf", 18);
    nameLabel->setAnchorPoint(Vec2(0.0f,0.5f)); // left align
    nameLabel->setColor(cocos2d::Color3B(255, 215, 0));
    nameLabel->setPosition(Vec2(_table_margin_left, _popup_size.y - _table_margin_top - _entry_margin_top * pos));

    addChild(nameLabel, 1);
    
    std::string sscore = std::to_string(score);
    Label* scoreLabel = Label::createWithTTF(sscore, "fonts/Pixel LCD-7.ttf", 18);
    scoreLabel->setAnchorPoint(Vec2(1.0f,0.5f)); // right align
    scoreLabel->setColor(cocos2d::Color3B(255, 255, 255));
    scoreLabel->setPosition(Vec2(
            _table_margin_left + 500,
            Director::getInstance()->getVisibleSize().height - _table_margin_top  - _entry_margin_top * pos
    ));
    addChild(scoreLabel, 1);

}

void HighscorePopup::initBackButton() {
    auto btn = ui::Button::create("res/back_button.png", "res/back_button_clicked.png");
    btn->setScale(0.4);
    btn->setPosition(Vec2(
            _popup_size.x / 2,
            100
    ));
    btn->addClickEventListener( CC_CALLBACK_1(HighscorePopup::BackButtonCallback, this) );
    // _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    addChild(btn, 1);
}

void HighscorePopup::close() {
    this->removeFromParentAndCleanup(true);
}





