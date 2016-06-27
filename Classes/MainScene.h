#pragma once

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#define TRANSITION_TIME 0.5

#include "cocos2d.h"

#define scaleFactorSnail 0.15f

using namespace cocos2d;




class MainScene : public Layer
{
    Size _screenSize;
    Vec2 _center;
    Vec2 _delta;
    Vec2 _tap;
    
    Sprite* _snail;
    
public:
    MainScene();
    virtual ~MainScene();
    virtual bool init();
    void menuCloseCallback(Ref* pSender);
    void respawn();
    
    static Scene* createScene();
    
    CREATE_FUNC(MainScene);
    
    bool onTouchBegan(Touch*, Event*);
    void onTouchMoved(Touch*, Event*);
    void onTouchEnded(Touch*, Event*);
};

#endif // __MAIN_SCENE_H__
