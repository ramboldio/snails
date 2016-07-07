#ifndef WinningScene_h
#define WinningScene_h

#include <stdio.h>
#include "cocos2d.h"

class WinningScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(WinningScene);
    
private:
    void goToMainScene(Ref *sender);
};



#endif /* WinningScene_h */
