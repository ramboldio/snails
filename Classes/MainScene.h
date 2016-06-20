#pragma once

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#define TRANSITION_TIME 0.5

#include "cocos2d.h"

using namespace cocos2d;


class MainScene : public Layer
{
    Size screenSize;
    
public:
    MainScene();
    virtual ~MainScene();
    virtual bool init();
    void menuCloseCallback(Ref* pSender);
    
    static Scene* createScene();
    
    CREATE_FUNC(MainScene);
};

#endif // __MAIN_SCENE_H__
