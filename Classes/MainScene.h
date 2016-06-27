#pragma once

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#define TRANSITION_TIME 0.5

#include "cocos2d.h"

using namespace cocos2d;


class MainScene : public Layer
{
    Size _screenSize;
    Vec2 _center;
    Vec2 _delta;
    Vec2 _force;
    Vec2 _tap;
    
    Sprite* _snail;
    
public:
    MainScene();
    virtual ~MainScene();
    virtual bool init();
    void menuCloseCallback(Ref* pSender);
    
    static Scene* createScene();
    
    CREATE_FUNC(MainScene);
    
    void onTouchesBegan(const std::vector<Touch*> &touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<Touch*> &touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<Touch*> &touches, cocos2d::Event* event);
    bool onContactBegin(PhysicsContact& contact);

private:
    void update(float dt);
};

#endif // __MAIN_SCENE_H__
