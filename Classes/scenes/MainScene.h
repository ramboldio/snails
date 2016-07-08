#pragma once

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#define TRANSITION_TIME 0.5
#define JUMPS_COUNT 10
#define HELPING_FORCE Vec2(1000,2000)
#define CUSTOM_GRAVITY Vec2(0.0f, -350.0f)
#define FALLING_FORCE Vec2(100000.0f,100000.0f)

#include "../helpers/ForceHandles.h"
#include "cocos2d.h"
#include "../model/Snail.h"

using namespace cocos2d;

// forward define
class ForceHandles;

class MainScene : public Layer
{
    Size _screenSize;
    Vec2 _center;
    Vec2 _delta;
    float deltaOne;
    Vec2 _force;
    Vec2 _touch_start;
    Vec2 _touch_stop;
    Vec2 _tap;
    Vec2 _gravity = CUSTOM_GRAVITY;
    int score = 0;
    int jumps = JUMPS_COUNT;
    Snail* _snail;
    ForceHandles* _handles;
    int glibberFlag;

public:
    MainScene();
    virtual ~MainScene();
    virtual bool init();
    void menuCloseCallback(Ref* pSender);
    
    static Scene* createScene();
    
    CREATE_FUNC(MainScene);
    void sun_way(Node* sun);
    void station_way(Node* station);
    void createSnail();
    void goToGameOverScene(Ref *sender);

    void onTouchesBegan(const std::vector<Touch*> &touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<Touch*> &touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<Touch*> &touches, cocos2d::Event* event);
    bool onContactBegin(PhysicsContact& contact);

        private:
    void update(float dt);
};

#endif // __MAIN_SCENE_H__
