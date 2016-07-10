//
// Created by lukas on 08.07.16.
//

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
    _messageLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
                                             Director::getInstance()->getVisibleSize().height - _heading_margin_top));
    addChild(_messageLabel, 1);

    Sprite* background = Sprite::create("res/highscore_background.png");
    addChild(background);

    drawEntries();
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
    Label* nameLabel = Label::createWithTTF(std::to_string(pos +1) + ". " + name, "fonts/Pixel LCD-7.ttf", 32);
    nameLabel->setAnchorPoint(Vec2(0.0f,0.5f)); // left align
    nameLabel->setColor(cocos2d::Color3B(255, 215, 0));
    nameLabel->setPosition(Vec2(_table_margin_left, Director::getInstance()->getVisibleSize().height - _table_margin_top  - _entry_margin_top * pos));
    addChild(nameLabel, 1);

    std::string sscore = std::to_string(score);
    Label* scoreLabel = Label::createWithTTF(sscore, "fonts/Pixel LCD-7.ttf", 32);
    scoreLabel->setAnchorPoint(Vec2(1.0f,0.5f)); // right align
    scoreLabel->setColor(cocos2d::Color3B(255, 255, 255));
    scoreLabel->setPosition(Vec2(
            _table_margin_left + 500,
            Director::getInstance()->getVisibleSize().height - _table_margin_top  - _entry_margin_top * pos
    ));
    addChild(scoreLabel, 1);

}

