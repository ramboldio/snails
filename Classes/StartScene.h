#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(StartScene);
    
private:
    void GoToMainScene(Ref *sender);
};

#endif // __START_SCENE_H__
