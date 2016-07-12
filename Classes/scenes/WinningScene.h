#ifndef WinningScene_h
#define WinningScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "../helpers/HighscorePopup.h"

class WinningScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(WinningScene);
    
private:
    void goToMainScene(Ref *sender);
    void goToStartScene(Ref *sender);
    void openHighscorePopup(Ref *sender);
};



#endif /* WinningScene_h */
