#ifndef __HIGHSCORE_SCENE_H__
#define __HIGHSCORE_SCENE_H__

#include "cocos2d.h"
#include "../model/Highscore.h"
#include "MainScene.h"

class HighScoreScene : public cocos2d::Layer
{
    Highscore* _model;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HighScoreScene);

    void displayScores();

private:
    void goToMainScene(Ref *sender);
};

#endif // __START_SCENE_H__
