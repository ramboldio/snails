//
// Created by lukas on 08.07.16.
//

#ifndef MYGAME_HIGHSCOREPOPUP_H
#define MYGAME_HIGHSCOREPOPUP_H

#include "cocos2d.h"
#include "../model/Highscore.h"

// using namespace cocos2d;

class HighscorePopup : public cocos2d::Layer{
public:
    HighscorePopup();
    ~HighscorePopup();

    static HighscorePopup *createPopup();

    void drawPopup();
    void close();

    virtual void draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
                       bool transformUpdated);

    Label* getMessageLabel() { return _messageLabel; };

private:
    Label* _messageLabel;
    Highscore* _model;

    int _heading_margin_top = 100;
    int _table_margin_top = _heading_margin_top + 100;
    int _table_margin_left = 250;
    int _entry_margin_top = 50;

    Vec2 _popup_size = Director::getInstance()->getVisibleSize();

    void drawTableHeader();
    void drawEntries();

    // low level draw funtion pos [0:10]
    void drawEntry(int pos, std::string &name, int &score);

    void initBackButton();
    void BackButtonCallback(Ref *pSender) {
        this->close();
    }

};


#endif //MYGAME_HIGHSCOREPOPUP_H
