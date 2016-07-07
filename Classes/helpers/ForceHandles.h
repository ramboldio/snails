#ifndef ForceHandles_h
#define ForceHandles_h

#include <stdio.h>
#include "MainScene.h"
#include "cocos2d.h"

using namespace cocos2d;

// forward define MainScene Class
class MainScene;

class ForceHandles : public Layer{

    MainScene *_scene;
    Vec2 _gravity;

    // apperance settings
    static const int _handleCount = 5;
    static const int _defaultHandleOffset = 20;

    void displayHandles(int count, Vec2 start_coord, Vec2 force);

public:
    ForceHandles(MainScene* s, Vec2 g);

    void displayHandles_onSnail(Vec2 force, Vec2 snail_pos);

    void clearHandles();

    static Sprite* _handleObjs [_handleCount];

    void drawHandle(Vec2 pos);
};


#endif //MYGAME_FORCEHANDLES_H
