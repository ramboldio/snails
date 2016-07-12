#ifndef GameOverScene_h
#define GameOverScene_h

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(GameOverScene);
    
private:
    void goToMainScene(Ref *sender);
    void goToStartScene(Ref *sender);
};

#endif /* GameOverScene_h */
